/*  timer.c
 *
 *  This file implements a benchmark timer using timer 2.
 *
 *  COPYRIGHT (c) 1989-1998.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  Ported to LEON implementation of the SPARC by On-Line Applications
 *  Research Corporation (OAR) under contract to the European Space 
 *  Agency (ESA).
 *
 *  LEON modifications of respective RTEMS file: COPYRIGHT (c) 1995. 
 *  European Space Agency.
 *
 *  $Id$
 */


#include <bsp.h>

rtems_boolean Timer_driver_Find_average_overhead;

rtems_boolean Timer_driver_Is_initialized = FALSE;

extern volatile LEON3_Timer_Regs_Map *LEON3_Timer_Regs;
extern void LEON3_Find_timer(void);
  

void Timer_initialize()
{
  LEON3_Find_timer();

  /*
   *  Timer runs long and accurate enough not to require an interrupt.
   */
  if (LEON3_Timer_Regs) {
    if ( Timer_driver_Is_initialized == FALSE ) {
      /* approximately 1 us per countdown */
      LEON3_Timer_Regs->reload_t1 = 0xffffff;
      LEON3_Timer_Regs->value_t1 = 0xffffff;
    } else {
      Timer_driver_Is_initialized = TRUE;
    }
    LEON3_Timer_Regs->conf_t1 = LEON3_GPTIMER_EN | LEON3_GPTIMER_LD;
  }
}

#define AVG_OVERHEAD      3  /* It typically takes 3.0 microseconds */
                             /*     to start/stop the timer. */
#define LEAST_VALID       2  /* Don't trust a value lower than this */

int Read_timer()
{
  uint32_t  total;

  if (LEON3_Timer_Regs) {
    total = LEON3_Timer_Regs->value_t1;
    
    total = 0xffffff - total;
    
    if ( Timer_driver_Find_average_overhead == 1 )
      return total;          /* in one microsecond units */
    
    if ( total < LEAST_VALID )
      return 0;            /* below timer resolution */
    
    return total - AVG_OVERHEAD;
  }
  return 0;
}

rtems_status_code Empty_function( void )
{
  return RTEMS_SUCCESSFUL;
}

void Set_find_average_overhead(
  rtems_boolean find_flag
)
{
  Timer_driver_Find_average_overhead = find_flag;
}
