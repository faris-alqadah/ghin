//! Author: Faris Alqadah
//!Uitlity for timing algorithms

#ifndef _TIMING_H
#define	_TIMING_H
#include<time.h>
#include <sys/times.h>
#include <unistd.h>
//! when timing starts
extern struct tms startTime;
//! when timing has ended
extern struct tms endTime; //when timiing ended
//! the time units
extern float clockTicksPerSecond;
//! start time converted to seconds
extern float startTimeSeconds;
//! end time converted to seconds
extern float endTimeSeconds; 

//! Call this to Start timing
 void StartTiming();

//! Call this to End timing
 void EndTiming();

//! Call this after StartTiming and EndTiming have been called to compute total CPU time
 /*!
  \sa StartTiming
  \sa EndTiming

  */
 float ComputeTime();
 
#endif	/* _TIMING_H */

