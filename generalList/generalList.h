#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;
enum Type
{
	HEAD,//ͷ����
	VALUE,//ֵ����
	SUB,//�ӱ�����
};
struct GeneralNode
{
	Type _type;//����
	GeneralNode *_next;//ָ��ͬ�����һ���ڵ�
	union
	{
		char _value;
		GeneralNode*_sublink;//��һ����������ֵҲ�������ӱ�
	};
	GeneralNode(Type type) :_type(type), _next(NULL)
	{}
	GeneralNode(Type type, const char&value)
		:_type(type)
		, _next(NULL)
		, _value(value)
	{}
};
class GeneralList
{
protected:
	GeneralNode*_head;
public:
	GeneralList() :_head(NULL)
	{}
	GeneralList(char*str)
	{
		_head = _CreateList(str);
	}
	GeneralList(const GeneralList& g)
	{
		_head = _Copy(g._head);
	}
	GeneralList& operator=(const GeneralList& g)
	{
		if (this != &g)
		{
			GeneralList tmp(g);
			std::swap(_head, tmp._head);
		}
		return *this;
	}
	~GeneralList()
	{
		_Destroy(_head);
	}
	size_t Size()
	{
		size_t size = _Size(_head);
		return size;
	}
	size_t Depth()
	{
		size_t depth = _Depth(_head);
		return depth;
	}
	void Display()
	{
		_Display(_head);
		cout << endl;
	}
protected:
	bool IsValue(char str)
	{
		if (str >= 'A'&&str <= 'Z' || str >= 'a'&&str <= 'z' || str >= '0'&&str <= '9')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	GeneralNode*_CreateList(char*str)
	{
		assert((*str == '('));
		++str;
		GeneralNode*head = new GeneralNode(HEAD);
		GeneralNode*cur = head;
		while (*str)
		{
			if (IsValue(*str))
			{
				//��Ч����
				cur->_next = new GeneralNode(VALUE, *str);
				cur = cur->_next;
				cur->_value = *str;
				++str;
				cur->_type = VALUE;
			}
			else if (*str==')')
			{
				//�ӱ�Ľ�����־
				str++;
				return head;
			}
			else if (*str == '(')
			{
				//�����б�
				cur->_next = new GeneralNode(SUB);
				cur = cur->_next;
				cur->_sublink = _CreateList(str);
				str++;
				cur->_type = SUB;
			}
			else
			{
				//���Ż��������ָ��
				str++;
			}
		}
		return head;
	}
	GeneralNode*_Copy(GeneralNode*head)
	{
		//phead,pcurΪҪ�����Ķ�����
		//head,curΪδ�����Ķ�����
		GeneralNode*phead = new GeneralNode(HEAD);
		GeneralNode*pcur = phead;
		GeneralNode*cur = head;
		while (cur)
		{
			if (cur->_type == VALUE)
			{
				pcur->_next = new GeneralNode(VALUE, cur->_value);
				pcur = pcur->_next;
				pcur->_value = cur->_value;
				cur = cur->_next;
			}
			else if (cur->_type == SUB)
			{
				pcur->_next = new GeneralNode(SUB);
				pcur = pcur->_next;
				pcur->_type = cur->_type;
				pcur->_sublink = _Copy(cur->_sublink);
				cur = cur->_next;
			}
			else
			{
				cur = cur->_next;
			}
		}
		return phead;
	}
	void _Destroy(GeneralNode*head)
	{
		GeneralNode*cur = head;
		while (cur)
		{
			GeneralNode*del = cur;
			cur = cur->_next;
			if (del->_type == SUB)
			{
				_Destroy(del->_sublink);
			}
			else
			{
				delete del;
				del = NULL;
			}
		}
	}
	void _Display(GeneralNode*head)
	{
		GeneralNode*cur = head;
		while (cur)
		{
			if (cur->_type == HEAD)
			{
				cout << "(";
			}
			else if (cur->_type == VALUE)
			{
				cout << cur->_value;
				if (cur->_next != NULL)
				{
					cout << ",";
				}
			}
			else
			{
				_Display(cur->_sublink);
				if (cur->_next != NULL)
				{
					cout << ",";
				}
			}
			cur = cur->_next;
		}
		cout << ")";
	}
	size_t _Size(GeneralNode*head)
	{
		size_t count = 0;
		GeneralNode*cur = head;
		while (cur)
		{
			if (cur->_type == VALUE)
			{
				count++;
			}
			else if (cur->_type == SUB)
			{
				count += _Size(cur->_sublink);
			}
			cur = cur->_next;
		}
		return count;
	}
	size_t _Depth(GeneralNode*head)
	{
		size_t maxDepth = 1;
		GeneralNode*cur = head;
		while (cur)
		{
			if (cur->_type == SUB)
			{
				size_t depth = _Depth(cur->_sublink) + 1;
				if (depth > maxDepth)
				{
					maxDepth = depth;
				}
			}
			cur = cur->_next;
		}
		return maxDepth;
	}
};