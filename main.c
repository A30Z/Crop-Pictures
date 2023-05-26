#include <stdio.h>
#include <stdlib.h>
#include <bmpio.h>
unsigned char pic[2000][2000][3];
unsigned char ans[2000][2000][3];

void crop(unsigned char x[2000][2000][3],int wid,int hei,char num[]){
	int maxt,mint,maxa,mina,m=0;
	for(int i=0;i<hei;i++){
 	for(int j=0;j<wid;j++){
 		if(!(x[i][j][0]==255 & x[i][j][1]==255 & x[i][j][2]==255)){
 			if(m==0){
 				maxt=i;
 				mint=i;
 				maxa=j;
 				mina=j;
 				m++;
			 }
			 if(i>maxt)
			 maxt=i;
			 if(i<mint)
			 mint=i;
			 if(j>maxa)
			 maxa=j;
			 if(j<mina)
			 mina=j;
		 }
	 }
 }
 wid=maxa-mina;
 hei=maxt-mint;

 for(int i=mint;i<maxt;i++){
 	for(int j=mina;j<maxa;j++){
 		ans[i-mint][j-mina][0]=x[i][j][0];
 		ans[i-mint][j-mina][1]=x[i][j][1];
 		ans[i-mint][j-mina][2]=x[i][j][2];
	 }
 }
 saveBMP(ans,wid,hei,num);
}

int main() {
 char p[100],m,t=0,q=0,l=0;
 gets(p);
 int wid,hei,maxt,mint,maxa,mina;
 readBMP(p,&wid,&hei,pic);
 int b=1;
char num[80];


 int h[100][2];
 int w[100][2];
 for(int i=0;i<100;i++){
 	h[i][0]=0; h[i][1]=0; w[i][0]=0; w[i][1]=0;
 }
 t=0;
 q=0;
 l=0;
for(int i=0;i<hei;i++){
	if(i==165)
	continue;
	l=0;
	for(int j=0;j<wid;j++){
		if(pic[i][j][0]!=255 & pic[i][j][1]!=255 & pic[i][j][2]!=255)
		l++;
	}
	if(q==0){
		if(l==0){
			if(i==0)
			h[t][0]=i;
			else
			h[t][0]=i+20;
			q=1;
			continue;
		}
	}
	else{
		if(l!=0){
			h[t][1]=i-20;
			q=0;
			t++;
		}
	}
	if(i==hei-1)
	h[t][1]=i;
}
int arz=t;
t=0;
q=0;
for(int j=0;j<wid;j++){
	l=0;
	for(int i=0;i<hei;i++){
		if((pic[i][j][0]!=255 & pic[i][j][1]!=255 & pic[i][j][2]!=255))
		l++;
	}
	if(q==0){
		if(l==0){
			if(j==0)
			w[t][0]=j;
			else
			w[t][0]=j+20;
			q=1;
			continue;
		}
	}
	else{
		if(l!=0){
			w[t][1]=j-20;
			q=0;
			t++;
		}
	}
	if(j==wid-1)
	w[t][1]=j;
}
int tool=t;
for(int i=0;i<tool;i++){
	for(int j=0;j<arz;j++){
		hei=h[i+1][0]-h[i][1];
		wid=w[j+1][0]-w[j][1];
		for(int f=0;f<hei;f++){
			for(int g=0;g<wid;g++){
				ans[f][g][0]=pic[f+h[i][1]][g+w[j][1]][0];
				ans[f][g][1]=pic[f+h[i][1]][g+w[j][1]][1];
				ans[f][g][2]=pic[f+h[i][1]][g+w[j][1]][2];
			}
		}
		sprintf( num,"ans%d.bmp",b);
		crop(ans,wid,hei,num);
		b++;
		
	}
}

 
	return 0;
}
