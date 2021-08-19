








#include<stdio.h>

#include <string.h>

int main()
{

 /*
 for(i =0;i<37;i++){
printf("%c\n",c_dic[i]);
 }
 */


/*
  printf("%d\n",lenght);
  printf("num\n");
  scanf("%d", &tint);
  printf("%d\n",tint);

  int lim=tint+3;
*/

  FILE *fpWrite=fopen("data.txt","w");
  if(fpWrite==NULL)
  {
      return 0;
  }
  int tint;
  char c_dic[]="abcdefghijklmnopqrstuvwxyz1234567890_";    
  int i;
  int lenght = strlen(c_dic);
 
  int iwei=5;
  int inum=iwei-1;
  int num;
  int ii;
  int nnum;
  int i2;
  int i3;
  int i4;
  int i5;
  for ( num=inum;num>=0;num--)
  {
//-----------
    
    
    if ((iwei-num)== 1){
      for ( i=0;i<37;i++)
      {
         for (ii=0;ii<1;ii++)
        {
          
            for (nnum=0;nnum<num;nnum++)
            {
              fprintf(fpWrite,"%c", c_dic[ii] );
            }
            fprintf(fpWrite,"%c\n", c_dic[i]);
          
        }
      }

    }
//-----------

    else if ((iwei-num)== 2){
      for (i=1;i<37;i++)
      {
        for (i2=0;i2<37;i2++){
          for (ii=0;ii<1;ii++)
          {
            for (nnum=0;nnum<num;nnum++)
            {
              fprintf(fpWrite,"%c", c_dic[ii] );
            }
            fprintf(fpWrite,"%c", c_dic[i]);
            fprintf(fpWrite,"%c\n", c_dic[i2]);
          }
        }
      }
    }


//-----------------------



    else if ((iwei-num)== 3){
      for (i=1;i<37;i++)
      {
        for (i2=0;i2<37;i2++){
          for (i3=0;i3<37;i3++){
            for (ii=0;ii<1;ii++)
            {
              for (nnum=0;nnum<num;nnum++)
              {
                fprintf(fpWrite,"%c", c_dic[ii] );
              }
              fprintf(fpWrite,"%c", c_dic[i]);
              fprintf(fpWrite,"%c", c_dic[i2]);
              fprintf(fpWrite,"%c\n", c_dic[i3]);
            }
          }
        }
      }
    }
    
     
    //-----------------------
       
    else if ((iwei-num)== 4){
      for (i=1;i<37;i++)
      {
        for (i2=0;i2<37;i2++){
          for (i3=0;i3<37;i3++){
            for (i4=0;i4<37;i4++){
              for (ii=0;ii<1;ii++)
              {
                for (nnum=0;nnum<num;nnum++)
                {
                  fprintf(fpWrite,"%c", c_dic[ii] );
                }
                fprintf(fpWrite,"%c", c_dic[i]);
                fprintf(fpWrite,"%c", c_dic[i2]);
                fprintf(fpWrite,"%c", c_dic[i3]);
                fprintf(fpWrite,"%c\n", c_dic[i4]);
              }
            }
          }
        }
      }
    }
    
    //-----------------------
       
       
      
      
    else if ((iwei-num)== 5){
      for (i=1;i<37;i++)
      {
        for (i2=0;i2<37;i2++){
          for (i3=0;i3<37;i3++){
            for (i4=0;i4<37;i4++){
              for (i5=0;i5<37;i5++){
                for (ii=0;ii<1;ii++)
                {
                  for (nnum=0;nnum<num;nnum++)
                  {
                    fprintf(fpWrite,"%c", c_dic[ii] );
                  }
                  fprintf(fpWrite,"%c", c_dic[i]);
                  fprintf(fpWrite,"%c", c_dic[i2]);
                  fprintf(fpWrite,"%c", c_dic[i3]);
                  fprintf(fpWrite,"%c", c_dic[i4]);
                  fprintf(fpWrite,"%c\n", c_dic[i5]);
                }
              }
            }
          }
        }
      }
    }

//-----------------------
   
  
  
    
  }




  fclose(fpWrite);
  return 0;
}

