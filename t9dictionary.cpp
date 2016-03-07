#include<fstream>
#define MAX 20
#include<iostream>
#include<string.h>
using namespace std;
#define ALPHABET_SIZE (26)
// Converts key current character into index
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define INDEX_TO_CHAR(i) ((char)i + 'a')
// structure of a trie node
//void mapNumTochar(char[]);
//char** searchkey(char,int);
class node
{
    int value;
    node *children[ALPHABET_SIZE];
    friend class trie;
};

// trie ADT
class trie
{
    node *root;
    //int count;
   public:
    trie();
    node* getNode();
    void insert(char key[]);
    void search(char key[]);
    void suggestions(node*,char key[]);
};
class NODE
{
   char *str;
   int isleaf,visited,parent;
   friend class tree;
};
class tree
{
  NODE n[100];
  int size,no_of_roots,no_of_leaf;
 public:
   tree()
   {
    size=-1;
    no_of_roots=0;no_of_leaf=0;
    for(int i=0;i<size;i++)
    {
      n[i].str=new char[2];
      strcpy(n[i].str," ");
      n[i].isleaf=0;
      n[i].visited=0;
      n[i].parent=-1;} 
   }
   void insertNODE(char **s,int counter,int k1);
   void traverse();
   void display();
};
trie t;
tree T;
void tree::traverse()
{
  int parent;
  char prefix[MAX];
  strcpy(prefix,"");
  if(no_of_roots-1 == size)
  {
    for(int k=0;k<=size;k++)
     t.search(n[k].str);
  }
  else
  {
  for(int i=0;i<no_of_roots;i++)
  {  parent=i;
     strcpy(prefix,n[i].str);
     //cout<<prefix;
     for(int k=0;k<no_of_leaf/no_of_roots;k++)
     {
     for(int j=no_of_roots;;j++)
     {
       if(n[j].visited!=1 && n[j].parent==parent)
       {//cout<<"BEFORE:"<<prefix<<"\n";
         strcat(prefix,n[j].str);//cout<<"AFTER:"<<prefix<<endl;
         n[j].visited=1;
         if(n[j].isleaf==1)
           break;
         else
           parent=j;
       }
     }
    if(strlen(prefix)>4)
     prefix[strlen(prefix)-1]='\0';
     t.search(prefix);
     strcpy(prefix,n[i].str);
    }
   }
}}
/*void tree::traverse()
{cout<<"REached traverse"<<endl;int j;char prefix[MAX];
  for(int i=size;i<=(size-no_of_roots+1);i--)
  {j=i;cout<<"\n"<<j<<"\n";
    do
    {
      strcpy(prefix,n[j].str);
      n[j].visited=1;
      j=n[j].parent;
     }while(j>-1);
    cout<<"PREFIX: "<<prefix<<endl;
  }
}*/
      
    
  void tree::insertNODE(char **s,int counter,int k1)
   {int crrct=0,l,z=0;
     if(k1==1)
     {//cout<<"CAME\n";
      no_of_roots=counter;
      for(int i=++size;i<counter;i++)
      {
       n[i].str=new char[strlen(s[i])+1];
       strcpy(n[i].str,s[i]);//cout<<"String copy success\n";
       if(z!=0)
        size++;
       n[i].isleaf=1;
       n[i].visited=0;
       n[i].parent=-1;z++;
      }
      no_of_leaf=counter;
     }
     //int crrct=1;
     else
     {
       int initialSize=size;
       for(int i=(initialSize-no_of_leaf+1);i<=initialSize;i++)
       {
         l=0;
         for(int j=++size;l<counter;j++)
         {
           n[j].str=new char[strlen(s[l]+1)];//cout<<s[i]<<endl;
           strcpy(n[j].str,s[l]);
           n[j].parent=i;
           n[j].isleaf=1;
           n[j].visited=0;
           l++;
           size=j; 
         }
       }
       for(int k=(initialSize-no_of_leaf+1);k<=initialSize;k++)
        {n[k].isleaf=0;}
       no_of_leaf=(no_of_leaf*counter);
      }
}

void mapNumTochar(char[],tree);
void searchkey(char,int,int,tree);
//void insertNODE(char

// Returns new trie node (initialized to NULLs)
node* trie:: getNode()
{
    node *newNode = NULL;
    newNode = new node;
    if(newNode)
    {
        int i;
        newNode->value = 0;
        //create pointer to all alphabets
        for(i = 0; i < ALPHABET_SIZE; i++)
        {
            newNode->children[i] = NULL;
        }
    }

    return newNode;
}

// Initializes trie (root is dummy node)
trie::trie()
{
    root = getNode();//creation of root node
    //count = 0;//level(root)=0
}

// If not present, insert key into trie
// If the key is prefix of trie node, just marks leaf node
void trie::insert(char key[])
{
    int level;
    int length = strlen(key);
    int index;
    node *temp;
    temp = root;
    for(level=0;level<length;level++)
    {
        index=CHAR_TO_INDEX(key[level]);
        if( !temp->children[index] )
        {
            temp->children[index]=getNode();
            //count++;
        }

        temp=temp->children[index];
        //temp->value=1;
    }
    // mark last node as leaf
    temp->value=1;
}


// Returns non zero, if key presents in trie
void trie::search(char key[])
{
    int level;
    int length = strlen(key);
    int index;
    node *temp;
    temp = root;
    for(level=0;level<length;level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if( !temp->children[index] )
        {
            return ;
        }

        temp=temp->children[index];
    }
    suggestions(temp,key);
}

void trie::suggestions(node* temp,char key[])
{
   char *c;int i,flag=1,j;
   for(i=0;i<26;i++)
   {
     if(temp->children[i]!=NULL)
     {
       c=new char[strlen(key)+2];
       strcpy(c,key);
       c[strlen(key)]=INDEX_TO_CHAR(i);
       c[strlen(key)+1]='\0';
       for(j=0;j<26;j++)
       {
         if(temp->children[i]->children[j]==NULL)
          continue;
         else
         {
          flag=0;
          break;
         }
        }
        if(flag)
        {
          cout<<c<<endl;
          delete c;
        }
        else
        {
         suggestions(temp->children[i],c);
        }
      }
    }
}
void searchkey(char k,int c,int count)
{int i;char **s;int counter=0;
  if(k=='2')
  {
    switch(c)
    {
      case 1:
        s=new char*[1];
        counter=1;
        strcpy(s[0],"a");//cout<<s[0]<<endl;
        T.insertNODE(s,counter,count);
     return ;
      case 2:
        s=new char*[2];
        counter=2;
        for(i=0;i<2;i++)
          s[i]=new char[3];
        strcpy(s[0],"aa");
        strcpy(s[1],"b");
        T.insertNODE(s,counter,count);
      return ;
      case 3:
        s=new char*[4];
        counter=4;
        for(i=0;i<4;i++)
          s[i]=new char[4];
        strcpy(s[0],"aaa");
        strcpy(s[1],"ab");
        strcpy(s[2],"ba");
        strcpy(s[3],"c");
        T.insertNODE(s,counter,count);
      return ;
    }
  }
  else if(k=='3')
  {
    switch(c)
    {
      case 1:
        s=new char*[1];
        counter=1;
        strcpy(s[0],"d");
        T.insertNODE(s,counter,count);
      return;
      case 2:
        s=new char*[2];
        counter=2;
        for(i=0;i<2;i++)
          s[i]=new char[3];
        strcpy(s[0],"dd");
        strcpy(s[1],"e");
        T.insertNODE(s,counter,count);
      return ;
      case 3:
        s=new char*[4];
        counter=4;
        for(i=0;i<4;i++)
          s[i]=new char[4];
        strcpy(s[0],"ddd");
        strcpy(s[1],"ed");
        strcpy(s[2],"de");
        strcpy(s[3],"f");
       T.insertNODE(s,counter,count);
      return ;
    }
  }
  if(k=='4')
  {
    switch(c)
    {
      case 1:
        s=new char*[1];
        counter=1;
        strcpy(s[0],"g");
        T.insertNODE(s,counter,count);      
       return;
      case 2:
        s=new char*[2];
        counter=2;
        for(i=0;i<2;i++)
          s[i]=new char[3];
        strcpy(s[0],"gg");
        strcpy(s[1],"h");
        T.insertNODE(s,counter,count);
      return ;
      case 3:
        s=new char*[4];
        counter=4;
        for(i=0;i<4;i++)
          s[i]=new char[4];
        strcpy(s[0],"ggg");
        strcpy(s[1],"gh");
        strcpy(s[2],"hg");
        strcpy(s[3],"i");
        T.insertNODE(s,counter,count);
      return ;
    }
  }
  if(k=='5')
  {
    switch(c)
    {
      case 1:
        s=new char*[1];
        counter=1;
        strcpy(s[0],"j");
        T.insertNODE(s,counter,count);
      return ;
      case 2:
        s=new char*[2];
        counter=2;
        for(i=0;i<2;i++)
          s[i]=new char[3];
        strcpy(s[0],"jj");
        strcpy(s[1],"k");
        T.insertNODE(s,counter,count);
      return ;
      case 3:
        s=new char*[4];
        counter=4;
        for(i=0;i<4;i++)
          s[i]=new char[4];
        strcpy(s[0],"jjj");
        strcpy(s[1],"jk");
        strcpy(s[2],"kj");
        strcpy(s[3],"l");
      T.insertNODE(s,counter,count);
      return ;
    }
  }
  if(k=='6')
  {
    switch(c)
    {
      case 1:
        s=new char*[1];
        counter=1;
        strcpy(s[0],"m");
        T.insertNODE(s,counter,count);
      return ;
      case 2:
        s=new char*[2];
        counter=2;
        for(i=0;i<2;i++)
          s[i]=new char[3];
        strcpy(s[0],"mm");
        strcpy(s[1],"n");
        T.insertNODE(s,counter,count);
      return ;
      case 3:
        s=new char*[4];
        counter=4;
        for(i=0;i<4;i++)
          s[i]=new char[4];
        strcpy(s[0],"mmm");
        strcpy(s[1],"mn");
        strcpy(s[2],"nm");
        strcpy(s[3],"o");
       T.insertNODE(s,counter,count);
      return ;
    }
  }
  if(k=='8')
  {
    switch(c)
    {
      case 1:
        s=new char*[1];counter=1;
        strcpy(s[0],"t");
        T.insertNODE(s,counter,count);
      return ;
      case 2:
        s=new char*[2];counter=2;
        for(i=0;i<2;i++)
          s[i]=new char[3];
        strcpy(s[0],"tt");
        strcpy(s[1],"u");
        T.insertNODE(s,counter,count);
      return ;
      case 3:
        s=new char*[4];counter=4;
        for(i=0;i<4;i++)
          s[i]=new char[4];
        strcpy(s[0],"ttt");
        strcpy(s[1],"tu");
        strcpy(s[2],"ut");
        strcpy(s[3],"v");
        T.insertNODE(s,counter,count);
      return ;
    }
  }
  if(k=='9')
  {
    switch(c)
    {
      case 1:
        s=new char*[1];counter=1;
        strcpy(s[0],"x");
        T.insertNODE(s,counter,count);
      return ;
      case 2:
        s=new char*[2];counter=2;
        for(i=0;i<2;i++)
          s[i]=new char[3];
        strcpy(s[0],"xx");
        strcpy(s[1],"y");
        T.insertNODE(s,counter,count);
      return ;
      case 3:
        s=new char*[4];counter=4;
        for(i=0;i<4;i++)
          s[i]=new char[4];
        strcpy(s[0],"xxx");
        strcpy(s[1],"xy");
        strcpy(s[2],"yx");
        strcpy(s[3],"z");
        T.insertNODE(s,counter,count);
      return ;
    }
  }
  else if(k=='7')
  {
    switch(c)
    {
      case 1:
        s=new char*[1];counter=1;
        strcpy(s[0],"p");
        T.insertNODE(s,counter,count);
      return ;
      case 2:
        s=new char*[2];counter=2;
        for(i=0;i<2;i++)
          s[i]=new char[3];
        strcpy(s[0],"pp");
        strcpy(s[1],"q");
        T.insertNODE(s,counter,count);
      return ;
      case 3:
        s=new char*[4];counter=4;
        for(i=0;i<4;i++)
          s[i]=new char[4];
        strcpy(s[0],"ppp");
        strcpy(s[1],"pq");
        strcpy(s[2],"qp");
        strcpy(s[3],"r");
        T.insertNODE(s,counter,count);
      return ;
      case 4:
        s=new char*[8];counter=8;
        for(i=0;i<8;i++)
          s[i]=new char[5];
        strcpy(s[0],"pppp");
        strcpy(s[1],"qpp");
        strcpy(s[2],"pqp");
        strcpy(s[3],"ppq");
        strcpy(s[4],"qq");
        strcpy(s[5],"pr");
        strcpy(s[6],"rp");
        strcpy(s[7],"s");
       T.insertNODE(s,counter,count);
      return ;
    }
  }
  else
   cout<<"Nothing";
}
void mapNumToChar(char key[])
{
	int i,k=0,count[10];
    //char str[MAX]="",char **s;
    count[0]=-1;
    count[1]=-1;
    for(i=0;i<strlen(key);i++)
    {
      if((key[i]==key[i-1]) && (i!=0) && ((count[(int)key[i]]<3) || ((int)key[i]==7 && count[7]<4 && key[i]==key[i-1] && i!=0)))
        count[(int)key[i]]++;
      else
        count[(int)key[i]]=1;
      if((count[(int)key[i]]<=2 && key[i]==key[i+1]) || ( key[i]=='7' && (count[7]<=3) && key[i]==key[i+1]))
       continue;

      else
      {k++;
       //cout<<key[i]<<"\t"<<count[(int)key[i]]<<endl;
       searchkey(key[i],count[(int)key[i]],k);
    }
  }
}
void tree::display()
{
  cout<<"LEAF:"<<no_of_leaf;
  cout<<"ROOT:"<<no_of_roots;
  
  for(int i=0;i<=size;i++)
  { cout<<n[i].str<<endl;cout<<"Parent:"<<n[i].parent<<endl;cout<<"Is leaf:"<<n[i].isleaf<<endl;}
}  
// Application File
int main()
{
    int i;
    //trie t;//tree T;
    //T=new tree;
    ifstream infile;
    char key[MAX];
    char output[][12] = {"not present", "present"};
    infile.open("/home/gomathi/Documents/dictionary.txt");
    while(1)
    {
      infile >> key;
      if(infile.eof())
        break;
      else
        t.insert(key);
    }
    infile.close();
    cout<<"Enter the number sequence\n";
    cin>>key;
    mapNumToChar(key);
    T.traverse();
    string choice;
    cout<<"Which word do you want to text?";
    cin>>choice;
  //T.display(); 
   return 0;
}
