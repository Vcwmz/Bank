#include <stdio.h>
#include <stdlib.h>
#include "bank.h"
void showdata()
{
    int i;
    printf("������Դ������:[");
    for(i=0; i<N; i++)
    {
        printf("%d ",all_resource[i]);
    }
    printf("]\n\n");

    printf("ϵͳĿǰ������Դ������Ϊ��[");
    for(i=0; i<N; i++)
    {
        printf("%d ",available[i]);
    }
    printf("]\n\n");

    printf("�������Ѿ��õ�����Դ��\n");
    printf("           ��Դ0    ��Դ1    ��Դ2\n");
    for(i=0; i<M; i++)
    {
        printf("����P%d       %d       %d       %d\n",i,allocation[i][0],allocation[i][1],allocation[i][2]);
    }
    printf("\n\n");

    printf("�������������Դ��\n");
    printf("           ��Դ0    ��Դ1    ��Դ2\n");
    for(i=0; i<M; i++)
    {
        printf("����P%d       %d       %d       %d\n",i,need[i][0],need[i][1],need[i][2]);
    }
    printf("\n\n");
}
void bank()
{
    int i=0,j,p;
    int l=0;
    char flag='Y';
    int ch;
    while(flag=='Y'||flag=='y'||flag==1)
    {
        printf("��������������Դ�Ľ��̺ţ���P0��P3,�����������룡����P");
        scanf("%d",&p);
        printf("������p%d�����������Դ����\n",p);
        for(i=0; i<N; i++)
        {
            printf("��Դ%d :",i);
            scanf("%d",&request[i]);
        }
        i=0;

        //������������available��,���ߴ��need��
        for(j=0; j<N; j++)
        {
            if(available[j]<request[j] || request[j]>need[p][j] )
            {
                printf("The number you enter was not satisfied\n");
                flag='N';
                break;
            }
        }
        //start checking for safety.
        printf("please enter the number ��1 for banker, 2 for Random\n");
        scanf("%d",&ch);
        if(ch==1)
        {
            if(flag=='Y'||flag=='y')
            {
                changedata(p);
                if(chkerr(p))
                {
                    rstordata(p);
                    showdata();
                }
                else
                    showdata();
            }
            else
                showdata();
        }
        else
        {
            if(flag=='Y'||flag=='y')
            {
                changedata(p);
                if(random(p))
                {
                    rstordata(p);
                    showdata();
                }
                else
                    showdata();
            }
            else
                showdata();
        }


        printf("\n\n");
        printf("�Ƿ������ʾ,��1������,��0���˳���ʾ: ");
        scanf("%d",&l);
        if(l==1)
            flag='Y';
        else
            flag='N';
    }

}
void changedata(int k)
{
    int i;
    for(i=0; i<N; i++)
    {
        available[i]=available[i]-request[i];
        allocation[k][i]=allocation[k][i]+request[i];
        need[k][i]=need[k][i]-request[i];
    }
}

void rstordata(int k)
{
    int i=0;
    for(i=0; i<N; i++)
    {
        available[i]=available[i]+request[i];
        allocation[k][i]=allocation[k][i]-request[i];
        need[k][i]=need[k][i]+request[i];
    }
}

int random(int k)
{
    int i,j;
    int x[3];
    int n=0;
    int work,finish[10];
    for(i=0;i<N;i++)
    {
        work=available[i];
        for(j=0;j<M;j++)
        {
            x[n++]=j;
            if(need[j][i]<=work)
            work=work+allocation[j][i];
            else
            {
                printf("Random filed,Because the need[%d][%d] is too big\n",j,i);
                return 1;
            }
        }
    }
    printf("random successful!\n");
    for(n=0;n<4;n++)
        printf("%d",x[n]);

    return 0;
}
int chkerr(int k)
{
    int i,j;
    int work,finish[10];
    int a[4];
    int n=0;

    for(i=0; i<M; i++) finish[i]=0;
    for(j=0; j<N; j++)
    {
        work=available[j];
        i=k;
        do
        {
            if(finish[i]==0 && need[i][j]<=work)
            {
                a[n++]=i;
                work=work+allocation[i][j];
                finish[i]=1;
                i=0;
            }
            else
            {
                i++;
            }
        }
        while(i<M);
        for(i=0; i<M; i++)
            if(finish[i]==0)
            {
                printf("ϵͳ����ȫ,����ʧ��\n");
                return 1;
            }
    }
    printf("ϵͳ��ȫ������ɹ�\n");
    printf("��ȫ����Ϊ��");
    for(n=0; n<4; n++)
    {
        printf("%d ",a[n]);
    }
    printf("\n\n");
    return 0;
}

int main()
{
    int i=0,j=0,sum=0;
    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            sum=sum+allocation[j][i];
        }
        available[i]=all_resource[i]-sum;
        if(available[i]<0)
        {
            available[i]=0;
        }
        sum=0;
    }

    for(i=0; i<N; i++)
        for(j=0; j<M; j++)
            need[j][i]=max[j][i]-allocation[j][i];

    showdata();
    bank();
    return 0;
}
