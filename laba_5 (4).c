#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
struct tree
{
	int data;
	struct tree*right;
	struct tree*left;
};
struct tree* read ()
{
	long n;
	scanf ("%ld", &n);
//	printf("%ld\n",n);
	long i,a;
	int flag;
	struct tree*t;
	struct tree*s;
	s = NULL;
	for (i=0;i<n;i++)
	{
		scanf ("%ld", &a);
		if (s==NULL)
		{
			s=(struct tree*)malloc (sizeof (struct tree));
			s->left=NULL;
			s->right=NULL;
			s->data=a;
		}
		else
		{
			flag=1;
			for (t=s;flag==1;)
			{
				if (a>t->data)
				{
					if (t->right!=NULL)
					t=t->right;
					else
					{
						t->right=(struct tree*)malloc(sizeof(struct tree));
						t=t->right;
						t->data=a;
						t->left=NULL;
						t->right=NULL;
						flag=0;
					}
				}
				else
				{
					if (t->left!=NULL)
					t=t->left;
					else
					{
						t->left=(struct tree*)malloc(sizeof(struct tree));
						t=t->left;
						t->data=a;
						t->left=NULL;
						t->right=NULL;
						flag=0;
					}
				}
				
			}
		}
	}
	return s;
}
void write (struct tree*s)
{
	if(s!=NULL)
	{
		if (s->left!=NULL)
		{
			write (s->left);
			free (s->left);
		}
		printf ("%d ", s->data);
		if (s->right!=NULL)
		{
			write (s->right);
			free (s->right);
		}
	}
//	free (s);
}
int main()
{
	struct tree*sort=NULL;
	sort=read();
	write (sort);
	if(sort!=NULL)
	free (sort);
	//else printf("%ld",0);
	sort=NULL;
	return 0;
}
