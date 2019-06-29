#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int a[100],b[100];//input and output arrays
int bucket[150][10],X1[20],Y1=1350,X2[20];
int n,flag=0,flag1=0,flag2=1,flag3=0,buckets = 0,cnt = 0;
int sort_type = 0; //type of sorting to apply. 0 for ascending order sort.
double px[150][10],py[150][10],screen_x;
char s[30] = "The input array is  :  ";
char head[30] = "BUCKET SORT";
char explain[100] = "On placing the input values into their respective buckets we get - ";

void init()
{
	glMatrixMode(GL_PROJECTION);
	if(X2[buckets-1]>=3000)
        screen_x = X2[buckets-1]+300;//initialize viewing screen accordingly
    else
        screen_x = 3000;
    gluOrtho2D(0,screen_x,0,3000);
	glMatrixMode(GL_MODELVIEW);
}
void clear_screen()
{
    glClearColor(0.85,0.85,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.35,0.25,0.60);
}
void delay(int x)
{
	for(int i=0;i<x;i++)
		for(int j=0;j<100;j++);
}
void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void swapf(double *a,double *b)
{
	double temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void display_ipop(int c[],char s[],int x,int y)
{
	glRasterPos2f(x,y);
	char *i;
	for(i=s;*i!='\0';i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*i);
	char s1[20];
	char sp =' ';
	for(int j=0;j<n;j++){
		sprintf(s1,"%d",c[j]);
		for(i=s1;*i!='\0';i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*i);
        for(int p = 0;p<4;p++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,sp);
	}
}

void display_int(int a,double x,double y){
    //displays a number
	char s[20],*i;
	sprintf(s,"%d",a);
	glRasterPos2f(x,y);
	for(i=s;*i!='\0';i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*i);
}
void display_string(char p[],int x,int y,void *font)
{
    //displays a string
    char *i;
    glRasterPos2f(x,y);
	for(i=p;*i!='\0';i++)
		glutBitmapCharacter(font,*i);
}
void welcome()
{
    GLfloat y = 2570;
    char buff[200];
    char *c;
    char head1[35] = "COMPUTER GRAPHICS MINI PROJECT";
    char head2[30] = "TOPIC : BUCKET SORT";
    char end[70] = "PRESS ANY KEY TO VISUALIZE BUCKET SORT";
    display_string(head1,screen_x/2-(screen_x/3000)*glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)head1),2850,GLUT_BITMAP_TIMES_ROMAN_24);
    display_string(head2,screen_x/2-(screen_x/3000)*glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)head2),2700,GLUT_BITMAP_TIMES_ROMAN_24);
    FILE *fp;
    if ((fp = fopen("C:\\Users\\S.C.R.PESHWA\\Desktop\\CG\\bucket_sort\\welcome.txt","r")) == NULL){
       printf("Error! opening file");
       // Program exits if the file pointer returns NULL.
       exit(1);
   }
   if(fp){
        while (fgets(buff,150,fp)!=NULL){
            glRasterPos2f(100,y);
            for (c=buff; *c!='\0'; c++)
            {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*c);
            }
            y -= 93;
        }
        fclose(fp);
    }
    display_string(end,screen_x/2-(screen_x/3000)*glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)end),70,GLUT_BITMAP_TIMES_ROMAN_24);
}
void thankyou()
{
    glViewport(0,0,screen_x/2 - 70,1000);
    glClearColor(0.72,0.92,0.97,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.22,0.35,0.50);
	char ty[30] = "THANK YOU!";
	char db[30] = "Done by  :";
	char m[30] = "S Meghana Peshwa";
	char musn[30] = "1CR16CS139" ;
	char ad[3] = "&";
	char s[30] = "Sophia Maria Augustine";
	char susn[30] = "1CR16CS164";
	char exit[40] = "PRESS ANY KEY TO EXIT";
    display_string(ty,1350,2200,GLUT_BITMAP_TIMES_ROMAN_24);
    display_string(db,1420,1950,GLUT_BITMAP_TIMES_ROMAN_24);
    display_string(m,1320,1750,GLUT_BITMAP_TIMES_ROMAN_24);
    display_string(musn,1380,1550,GLUT_BITMAP_TIMES_ROMAN_24);
    display_string(ad,1490,1400,GLUT_BITMAP_TIMES_ROMAN_24);
    display_string(s,1280,1250,GLUT_BITMAP_TIMES_ROMAN_24);
    display_string(susn,1380,1050,GLUT_BITMAP_TIMES_ROMAN_24);
    display_string(exit,1240,400,GLUT_BITMAP_TIMES_ROMAN_24);
}
void display_bucket()
{
	int j=0;
	int p=0,x,y;
	double d;
	char s1[30],s2[10]=" - ",s3[30];
	for(int i=0;i<150;i++)
	{
		j=0;
		if(bucket[i][0]!=9999){
            x = i*10;
            y = x+9;
			while(bucket[i][j]!=9999){
				display_int(bucket[i][j],px[i][j],py[i][j]);
				j++;
			}
            d = (X2[p]-(X2[p]-X1[p])/2);
            sprintf(s3,"%d",x);
            sprintf(s1,"%d",y);
            strcat(s3,s2);
            strcat(s3,s1);
            //display range of each bucket
            display_string(s3,d-(screen_x/3000)*glutBitmapLength(GLUT_BITMAP_HELVETICA_18,(unsigned char*)s3),Y1-450,GLUT_BITMAP_HELVETICA_18);
            //draw buckets
			glLineWidth(5);
			glBegin(GL_LINE_LOOP);
			glVertex2f(X1[p],Y1+300);
			glVertex2f(X1[p],Y1-300);
			glVertex2f(X2[p],Y1-300);
			glVertex2f(X2[p],Y1+300);
			glEnd();
			p++;
		}
	}
}
void redisplay()
{
	clear_screen();
	//display heading
    display_string(head,screen_x/2-(screen_x/3000)*glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)head),2700,GLUT_BITMAP_TIMES_ROMAN_24);
	display_ipop(a,s,140,2250);//display input array
	if(flag1==1){
        //display buckets
        display_string(explain,140,2000,GLUT_BITMAP_TIMES_ROMAN_24);
        display_bucket();
	}
	glFlush();
}

void split()
{
	int p,j;
	int x=300,y=1350;//initial positions
	int m=0;
	for(int i=0;i<n;i++){
		p = a[i]/10;
		for(j=0;bucket[p][j]!=9999;j++);//finding empty slot in the bucket
		bucket[p][j] = a[i];//storing input number in that bucket
	}
	for(int i=0;i<150;i++)
	{
		j=0;
		if(bucket[i][0]!=9999){//looking for non empty bucket
			buckets++;
			//X1 and X2 arrays are required to draw the buckets
			X1[m] = x-160;
			while(bucket[i][j]!=9999){
                //storing positions of each number
				px[i][j]=x;
				py[i][j]=y;
				x=x+180;
				j++;
			}
			X2[m] = x+22;
			m++;
		x=x+380;
		}
	}
}
void translate_num(){
    //this function moves the numbers to be sorted in a semi circle fashion
	double angle1=M_PI,angle2=0,rx=90,ry=100,px1,py1,px2,py2;
	int i,j,p,q=0;
	for(p=0;p<150;p++)
	{
		q=0;
		if(bucket[p][0]!=9999){
			while(bucket[p][q]!=9999){
				q++;
			}
			//bubble sort
            for(i=0;i<q-1;i++)
            {
                for(j=0;j<q-i-1;j++)
                {

                    angle1=M_PI;
                    angle2=0;
                    if(sort_type==0){
                        if(bucket[p][j]>bucket[p][j+1]){ //for ascending order sort
                            px1=px[p][j]+90;
                            py1=py[p][j];
                            px2=px[p][j+1]-90;
                            py2=py[p][j+1];
                            while((angle2>=-M_PI) && (angle1>=0)){
                                px[p][j]=px1+cos(angle1)*rx;
                                py[p][j]=py1+sin(angle1)*ry;
                                angle1=angle1-(0.5*M_PI/180);
                                px[p][j+1]=px2+cos(angle2)*rx;
                                py[p][j+1]=py2+sin(angle2)*ry;
                                angle2=angle2-(0.5*M_PI/180);
                                redisplay();//re display entire screen with updated positions of numbers
                            }
                        swap(&bucket[p][j],&bucket[p][j+1]);//swap the numbers
                        swapf(&px[p][j],&px[p][j+1]);//swap the positions of the numbers
                        }
                    }

                    else if(sort_type==1){
                        if(bucket[p][j]<bucket[p][j+1]){ //for descending order sort
                            px1=px[p][j]+90;
                            py1=py[p][j];
                            px2=px[p][j+1]-90;
                            py2=py[p][j+1];
                            while((angle2>=-M_PI) && (angle1>=0)){
                                px[p][j]=px1+cos(angle1)*rx;
                                py[p][j]=py1+sin(angle1)*ry;
                                angle1=angle1-(0.5*M_PI/180);
                                px[p][j+1]=px2+cos(angle2)*rx;
                                py[p][j+1]=py2+sin(angle2)*ry;
                                angle2=angle2-(0.5*M_PI/180);
                                redisplay();//re display entire screen with updated positions of numbers
                            }
                        swap(&bucket[p][j],&bucket[p][j+1]);//swap the numbers
                        swapf(&px[p][j],&px[p][j+1]);//swap the positions of the numbers
                        }
                    }
                }
            }
            delay(1500);
        }
    }
}

void display()
{
    glClearColor(1,0.90,0.90,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.65,0,0.4);
    if(flag2==1)
        welcome();//display welcome page
	else if(flag2==0){
        redisplay();
        if(flag==1){
            translate_num();
            int j,p=0,b[n];
            if(sort_type==0){
            for(int i=0;i<150;i++)
            {
                j=0;
                if(bucket[i][0]!=9999){//check for non empty bucket
                    while(bucket[i][j]!=9999){//loop till last value stored in that bucket
                        b[p]=bucket[i][j];//store sorted values in another array
                        p++;
                        j++;
                    }
                }
            }
            }
            else if(sort_type==1){
            for(int i=149;i>=0;i--)
            {
                j=0;
                if(bucket[i][0]!=9999){//check for non empty bucket
                    while(bucket[i][j]!=9999){//loop till last value stored in that bucket
                        b[p]=bucket[i][j];//store sorted values in another array
                        p++;
                        j++;
                    }
                }
            }
            }
            delay(1300);
            char s1[30] = "The sorted array is  :  ";
            if(cnt==0){
                cnt++;
                printf(s1);
                for(int i=0;i<n;i++)
                    printf("%d  ",b[i]);
            }
            display_ipop(b,s1,140,500);
        }
	}
	if(flag3==1)
        thankyou();

	glFlush();
}


void menu(int id)
{
    /*if(id==4){
        flag2=0;
        glutRemoveMenuItem(1);//removing irrelevant menu items
        glutRemoveMenuItem(1);
        glutAddMenuEntry("Split into buckets",1);
        glutAddMenuEntry("Quit",5);
    }*/
	//if(id==1){
		//flag1=1;//to display input values split into buckets
        //glutRemoveMenuItem(1);
        //glutRemoveMenuItem(1);
        //glutAddMenuEntry("Ascending order sort",2);
        //glutAddMenuEntry("Descending order sort",3);
        //glutAddMenuEntry("Quit",5);
	//}
    if(id==2||id==3){
        flag=1;//to sort input values
        if(id==2)
            sort_type=0;
        else
            sort_type=1;
        //glutRemoveMenuItem(1);
        //glutRemoveMenuItem(1);
        //glutRemoveMenuItem(1);
        //glutAddMenuEntry("Quit",5);
    }
	else if(id==5){
        flag3=1;//to display thank you page
        /*if(flag2==1||flag1==0||flag==0)
            glutRemoveMenuItem(1);
        glutRemoveMenuItem(1);*/
	}
	glutPostRedisplay();
}
void mouse(int btn,int state,int x,int y)
{
    if(flag2==0&&flag1==0)
    {
        if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
                flag1=1;
                display();
        }
    }
}
void key(unsigned char a,int x,int y)
{
    if(flag2==1)
        flag2=0;
    if(flag3==1){
        exit(0);//exit to terminal
    }
     glutPostRedisplay();
}

int main(int argc,char **argv)
{
	printf("Enter the number of integers : ");
	scanf("%d",&n);
	int i,j;
	printf("Enter the integers : ");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);//store values in input array
	}
	for(i=0;i<150;i++)
		for(j=0;j<10;j++)
			bucket[i][j] = 9999;//initializing bucket values to 9999
    split();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("Bucket sort");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(3000,3000);
	init();
	glutFullScreen();
	glutMouseFunc(mouse);
    glutKeyboardFunc(key);
	glutDisplayFunc(display);
	glutCreateMenu(menu);
    glutAddMenuEntry("Ascending order sort",2);
    glutAddMenuEntry("Descending order sort",3);
    glutAddMenuEntry("Quit",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

