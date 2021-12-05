//区分词的原则：凡是一个非字母或数字的字符跟在字母或数字的后面，那么这个字母
   //或数字就是单词的词尾
   //允许线程使用互斥锁来修改临界资源，确保线程间的同步或协作。如果两个线程需要
   //安全地共享一个公共计数器，需要把公共计数器加锁线程需要访问称为互斥锁的变量
  //，它可以使线程间更好的工作，避免对于资源的访问冲突。
   #include <stdio.h>
   #include <pthread.h>
   #include <ctype.h>
   #include <stdlib.h>
 
  //互斥信号量
  pthread_mutex_t counter_clock=PTHREAD_MUTEX_INITIALIZER;
  
  
  int main(int ac,char *av[])
  {
    void *count_words(void *);
    //调试格式
    if(ac!=3)
    {
      printf("Usage:%s file1 file2\n",av[0]);
      exit(1);
    }
  
   //线程tidp1,tidp2
    pthread_t tidp1,tidp2;
    int error1,error2;
    //创建线程1，error1
    //创建线程2，error2
    error1=pthread_create(&tidp1,NULL,count_words,av[1]);
    error2=pthread_create(&tidp2,NULL,count_words,av[2]);
   //让线程1和2进入等待态
    pthread_join(tidp1,NULL);
    pthread_join(tidp2,NULL);
    return 0;
  }
  
  //线程函数，即统计一个文件的单词个数的函数
  void *count_words(void *f)
  {
   char *filename=(char *)f;
    FILE *fp;
    int c,prevc='\0';
    int total_words=0;
  
    if((fp=fopen(filename,"r"))!=NULL){
      while((c=getc(fp))!=EOF)
      {
        if(!isalnum(c) && isalnum(prevc)){
           pthread_mutex_lock(&counter_clock);
           total_words++;
           pthread_mutex_unlock(&counter_clock);
         }
         prevc=c;
     }
      fclose(fp);
      printf("total_words=%d\n",total_words);
    }else{
          perror(filename);
   }
   return NULL;
  }

