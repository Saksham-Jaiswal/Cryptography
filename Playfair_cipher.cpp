#include<bits/stdc++.h>
using namespace std;

string rectifyKey(string &s)  // O(s.size())
{
	string rectifiedKey;
	vector<bool> uniqueChars(26,0);
	for(char c:s)
	{
		int num=c+0;
		if((num>=65 && num<=90) || num>=97 && num<=122) // only considering the alphabets of the key
		{
			if(num>=64 && num<=90) num+=32; // converting uppercase alphabets to lowercase
			if(!uniqueChars[num-97]) 
			{
				if(num==105) uniqueChars[num-97+1]=1; // if i appears first then marking uniqueChars[j]=1
				if(num==106) uniqueChars[num-97-1]=1; // if j appears first then marking uniqueChars[i]=1 i.e if in key i and j both appears then only 1 we need to take and we take the one which appears first in the key
				rectifiedKey.push_back((char)num);
				uniqueChars[num-97]=1;
			}		
		}		
	}
	return rectifiedKey;
}

void generateKey(string &s, char (*m)[5])  // O(25)  
{
	s=rectifyKey(s);
	vector<bool> chars(26,0);
	int cnt=0;
	int incre=0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(cnt==s.size())
			{
				while(chars[incre]==1)
				{
					incre++;
				}
				if((incre==8 && chars[9]) || (incre==9 && chars[8])) // j is already present in chars but i is not or if i is already and present and j is not
				{
					incre++;
					while(chars[incre]==1)
					{
						incre++;
					}
				}
				if(incre==8) chars[9]=1; // when neither i and nor j is present in chars
				m[i][j]=(char)(97+incre++);
			}
			else 
			{
				chars[s[cnt]-97]=1;
				m[i][j]=s[cnt++];
			}
		}
	}	
}
  
void print(char (*m)[5])  // O(25)
{
	cout<<"Key Matrix is: \n";
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
			cout<<m[i][j]<<" ";
		cout<<"\n";	
	}
}

string rectifyPlainText(string &s)
{
	string pt;
	for(char c:s)
	{
		if(c==' ') continue;
		int num=c+0;
		if(num>=65 && num<=90) num+=32;
		pt.push_back((char)num);
	}
	return pt;
}

string diagram(string &s)
{
	string newPlainText;
	for(int i=0;i<s.size();i++)
	{
		newPlainText.push_back(s[i]);
		if((i%2==0) && s[i]==s[i+1]) newPlainText.push_back('x');		
	}
	if((newPlainText.size()) % 2) newPlainText.push_back('x');
	return newPlainText;
}

string encrypt(string &s,string &k,char (*m)[5])
{
	generateKey(k,m);
	print(m);
	s=rectifyPlainText(s);
	s=diagram(s);
	string ct;
	for(int k=0;k<s.size();k+=2)
	{
		int index1r=-1,index1c=-1;
		int index2r=-1,index2c=-1;
		bool flag=false;
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				if(m[i][j]==s[k])
				{
					index1r=i;
					index1c=j;
				}
				if(m[i][j]==s[k+1])
				{
					index2r=i;
					index2c=j;
				}
				if(index1r!=-1 && index1c!=-1 && index2r!=-1 && index2c!=-1)
				{
					if(index1r == index2r) // elements are in the same row
					{
						ct.push_back(m[index1r][(index1c+1)%5]);
						ct.push_back(m[index2r][(index2c+1)%5]);
					}
					else if(index1c == index2c) // elements are in the same column
					{
						ct.push_back(m[(index1r+1)%5][index1c]);
						ct.push_back(m[(index2r+1)%5][index2c]);
					}
					else
					{
						ct.push_back(m[index1r][index2c]);
						ct.push_back(m[index2r][index1c]);
					}
					flag=true;
					break;
				}
			}
			if(flag) break;
		}
	}
	return ct;
}
 
int main()
{
	string key,plainText,cipherText;
	char keyMatrix[5][5];
	cout<<"Please enter the key: \n";
	getline(cin,key); // key is case insensitive, user's key could contain whitespaces and numbers which we will eliminate when we rectify the key
	cout<<"Please enter the palintext(the plaintext must only contain alphabets without any whitespaces): \n";
	getline(cin,plainText);
	cipherText=encrypt(plainText,key,keyMatrix);
	cout<<cipherText;
	return 0;
}