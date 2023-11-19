#include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <math.h>
# include <omp.h>
#include <papi.h>
#include <memory.h>
#include <malloc.h>
int ins_count_no=0;
int main ( int argc, char *argv[] );
void compute ( int np, int nd, double pos[], double vel[], 
  double mass, double f[], double *pot, double *kin );
double dist ( int nd, double r1[], double r2[], double dr[] );
void initialize ( int np, int nd, double box[], int *seed, double pos[], 
  double vel[], double acc[] );
double r8_uniform_01 ( int *seed );
void timestamp ( void );
void update ( int np, int nd, double pos[], double vel[], double f[], 
  double acc[], double mass, double dt );
static void test_fail(char *file, int line, char *call, int retval);
int PAPI_get_dmem_info(PAPI_dmem_info_t * dmem );

/******************************************************************************/

int main ( int argc, char *argv[] )

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for MD_OPEN_MP.

  Discussion:

    MD implements a simple molecular dynamics simulation.

    The program uses Open MP directives to allow parallel computation.

    The velocity Verlet time integration scheme is used. 

    The particles interact with a central pair potential.

  Modified:

    14 July 2008

  Author:

    Bill Magro, Kuck and Associates, Inc.
    C version by John Burkardt

  Parameters:

    None
*/
{
  double *acc;
  double *box;
  double dt = 0.0001;
  double e0;
  double *ee;
  double *force;
  int i;
  int id;
  double *ke;
  double kinetic;
  double mass = 1.0;
  int nd = 3;
  int np = 500;
  double *pe;
  double *pos;
  double potential;
  int proc_num;
  int seed = 123456789;
  int step;
  int step_num = 1000;
  int thread_num;
  double *vel;
  double wtime;
   long long flpins;
  int retval,Events[2]= {PAPI_TOT_CYC, PAPI_TOT_INS};
  long_long values[2];
  timestamp ( );
 extern void dummy(void *);
 
  float real_time, proc_time, mflops;




//printf("%d",VALUE); 
PAPI_dmem_info_t dmem;

  clock_t c0, c1;
  double cputime;
  //proc_num = omp_get_num_procs ( );

  acc = ( double * ) malloc ( nd * np * sizeof ( double ) );
  box = ( double * ) malloc ( nd * sizeof ( double ) );
  ee = ( double * ) malloc ( step_num * sizeof ( double ) );
  force = ( double * ) malloc ( nd * np * sizeof ( double ) );
  ke = ( double * ) malloc ( step_num * sizeof ( double ) );
  pe = ( double * ) malloc ( step_num * sizeof ( double ) );
  pos = ( double * ) malloc ( nd * np * sizeof ( double ) );
  vel = ( double * ) malloc ( nd * np * sizeof ( double ) );


 /* printf ( "\n" );
  printf ( "MD_OPEN_MP\n" );
  printf ( "  C/OpenMP version\n" );
  printf ( "\n" );
  printf ( "  A molecular dynamics program.\n" );

  printf ( "\n" );
  printf ( "  NP, the number of particles in the simulation is %d\n", np );
  printf ( "  STEP_NUM, the number of time steps, is %d\n", step_num );
  printf ( "  DT, the size of each time step, is %f\n", dt );
  printf ( "\n" );
  printf ( "  The number of processors available is %d\n", proc_num );*/

/*
# pragma omp parallel private ( id )  
  {
    id = omp_get_thread_num ( );

    if ( id == 0 )
    {
      thread_num = omp_get_num_threads ( );
    /*  printf ( "\n" );
      printf ( "  Calling OMP_GET_NUM_THREADS inside a\n" );
      printf ( "  parallel region, we get the number of\n" );
      printf ( "  threads is %d\n", thread_num );
    }
  }

if (PAPI_stop_counters (values, 2) !=  PAPI_OK) {
    printf("Error stopping counters1\n");
    exit(1);
  }

  printf("PAPI_TOT_CYC = %lld\n", values[0]);
  printf("PAPI_TOT_INS_1 = %lld", values[1]);

*/
if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
exit(1);
retval = PAPI_library_init(PAPI_VER_CURRENT);
if (retval != PAPI_VER_CURRENT)
PAPI_start_counters (Events, 2);

if((retval=PAPI_flops( &real_time, &proc_time, &flpins, &mflops))<PAPI_OK)
    test_fail(__FILE__, __LINE__, "PAPI_flops", retval);

  c0 = clock();


/*
  Set the dimensions of the box.
*/
  for ( i = 0; i < nd; i++ )
  {
    box[i] = 10.0;
  }

  printf ( "\n" );
  printf ( "  Initialize positions, velocities, and accelerations.\n" );
/*
  Set initial positions, velocities, and accelerations.
*/
  initialize ( np, nd, box, &seed, pos, vel, acc );
/*
  Compute the forces and energies.
*/
  printf ( "\n" );
  printf ( "  Compute initial forces and energies.\n" );

  compute ( np, nd, pos, vel, mass, force, &potential, &kinetic );

  e0 = potential + kinetic;

  printf ( "\n" );
  printf ( "  Initial Total energy = %f\n", e0 );

/*
  This is the main time stepping loop:
    Compute forces and energies,
    Update positions, velocities, accelerations.
*/
 // wtime = omp_get_wtime ( );

  for ( step = 0; step < step_num; step++ )
  {
    compute ( np, nd, pos, vel, mass, force, &potential, &kinetic );

    pe[step] = potential;
    ke[step] = kinetic;
    ee[step] = ( potential + kinetic - e0 ) / e0;

    update ( np, nd, pos, vel, force, acc, mass, dt );
  }
 // wtime = omp_get_wtime ( ) - wtime;
/*
  Just for timing accuracy, we have moved the I/O out of the computational loop.
*/
  printf ( "\n" );
//  printf ( "  At each step, we report the potential and kinetic energies.\n" );
  //printf ( "  The sum of these energies should be a constant.\n" );
 // printf ( "  As an accuracy check, we also print the relative error\n" );
//  printf ( "  in the total energy.\n" );
  printf ( "\n" );
  printf ( "      Step      Potential       Kinetic        (P+K-E0)/E0\n" );
 // printf ( "                Energy          Energy         Energy Error\n" );
  printf ( "\n" );
  c1= clock();
 cputime = (c1 - c0)/(CLOCKS_PER_SEC );

printf ("\tElapsed CPU time test:   %f  sec\n",cputime);
  for ( step = 0; step < step_num; step++ )
  {
//    printf ( "  %8d  %14f  %14f  %14e\n", step + 1, pe[step], ke[step], ee[step] );
  }

  printf ( "\n" );
 // printf ( "  Elapsed wall clock time for main computation:\n" );
  //printf ( "  %f seconds.\n", wtime );

/*if (PAPI_stop_counters (values, 2) !=  PAPI_OK) {
    printf("Error stopping counters\n");
    exit(1);
  }*/
if((retval=PAPI_flops( &real_time, &proc_time, &flpins, &mflops))<PAPI_OK)
    test_fail(__FILE__, __LINE__, "PAPI_flops", retval);
 printf("Real_time:\t%f\nProc_time:\t%f\nTotal flpins:\t%lld\nMFLOPS:\t\t%f\n",
  real_time, proc_time, flpins, mflops);
  printf("%s\tPASSED\n", __FILE__);
PAPI_get_dmem_info(&dmem);
PAPI_stop_counters (values, 2);
// printf("PAPI_TOT_CYC = %lld\n", values[0]);
 // printf("PAPI_TOT_INS = %lld\n", values[1]);

printf("Peak Resident:\t%lld\n",dmem.high_water_mark);
  printf("PAPI_TOT_CYC = %lld\n", values[0]);
  printf("PAPI_TOT_INS = %lld\n*****%lld*****\n",ins_count_no++, values[1]);

  free ( acc );
  free ( box );
  free ( ee );
  free ( force );
  free ( ke );
  free ( pe );
  free ( pos );
  free ( vel );

  printf ( "\n" );
  printf ( "MD_OPEN_MP\n" );
  printf ( "  Normal end of execution.\n" );

  printf ( "\n" );
  timestamp ( );

  return 0;

PAPI_shutdown();
  exit(0);

}
static void test_fail(char *file, int line, char *call, int retval)
{

    printf("%s\tFAILED\nLine # %d\n", file, line);
    if ( retval == PAPI_ESYS ) {
        char buf[128];
        memset( buf, '\0', sizeof(buf) );
        sprintf(buf, "System error in %s:", call );
        perror(buf);
    }
    else if ( retval > 0 ) {
        printf("Error calculating: %s\n", call );
    }
    else {
        char errstring[PAPI_MAX_STR_LEN];
        PAPI_perror(retval, errstring, PAPI_MAX_STR_LEN );
        printf("Error in %s: %s\n", call, errstring );
    }
    printf("\n");
    exit(1);
}

/******************************************************************************/

void compute ( int np, int nd, double pos[], double vel[], 
  double mass, double f[], double *pot, double *kin )

/******************************************************************************/
/*
  Purpose:

    COMPUTE computes the forces and energies.

  Discussion:

    The computation of forces and energies is fully parallel.

    The potential function V(X) is a harmonic well which smoothly
    saturates to a maximum value at PI/2:

      v(x) = ( sin ( min ( x, PI2 ) ) )**2

    The derivative of the potential is:

      dv(x) = 2.0 * sin ( min ( x, PI2 ) ) * cos ( min ( x, PI2 ) )
            = sin ( 2.0 * min ( x, PI2 ) )

  Modified:

    21 November 2007

  Author:

    Bill Magro, Kuck and Associates, Inc.
    C version by John Burkardt

  Parameters:

    Input, int NP, the number of particles.

    Input, int ND, the number of spatial dimensions.

    Input, double POS[ND*NP], the position of each particle.

    Input, double VEL[ND*NP], the velocity of each particle.

    Input, double MASS, the mass of each particle.

    Output, double F[ND*NP], the forces.

    Output, double *POT, the total potential energy.

    Output, double *KIN, the total kinetic energy.
*/
{
  double d;
  double d2;
  int i;
  int j;
  int k;
  double ke;
  double pe;
  double PI2 = 3.141592653589793 / 2.0;
  double rij[3];

  pe = 0.0;
  ke = 0.0;
  long long flpins;
  int retval,Events[2]= {PAPI_TOT_CYC, PAPI_TOT_INS};
  long_long values[2];

/*
 if (PAPI_start_counters (Events, 2) != PAPI_OK) {
    printf("Error starting counters2\n");
    exit(1);
  }


# pragma omp parallel for default ( shared ) shared ( nd ) private ( i, j, k, rij, d, d2 ) reduction ( + : pe, ke ) */
  for ( k = 0; k < np; k++ )
  {
/*
  Compute the potential energy and forces.
*/
    for ( i = 0; i < nd; i++ )
    {
      f[i+k*nd] = 0.0;
    }

    for ( j = 0; j < np; j++ )
    {
      if ( k != j )
      {
        d = dist ( nd, pos+k*nd, pos+j*nd, rij );
/*
  Attribute half of the potential energy to particle J.
*/
        if ( d < PI2 )
        {
          d2 = d;
        }
        else
        {
          d2 = PI2;
        }

        pe = pe + 0.5 * pow ( sin ( d2 ), 2 );

        for ( i = 0; i < nd; i++ )
        {
          f[i+k*nd] = f[i+k*nd] - rij[i] * sin ( 2.0 * d2 ) / d;
        }
      }
    }

/*
if (PAPI_stop_counters (values, 2) !=  PAPI_OK) {
    printf("Error stopping counters2\n");
    exit(1);
  }

  printf("PAPI_TOT_CYC = %lld\n", values[0]);
  printf("PAPI_TOT_INS22 = %lld\n", values[1]);

*/

/*
  Compute the kinetic energy.
*/
    for ( i = 0; i < nd; i++ )
    {
      ke = ke + vel[i+k*nd] * vel[i+k*nd];
    }
  }
/*
if (PAPI_stop_counters (values, 2) !=  PAPI_OK) {
    printf("Error stopping counters2\n");
    exit(1);
  }

  printf("PAPI_TOT_CYC = %lld\n", values[0]);
  printf("PAPI_TOT_INS_2 = %lld\n", values[1]);*/

  ke = ke * 0.5 * mass;
  
  *pot = pe;
  *kin = ke;

  return;
}
/******************************************************************************/

double dist ( int nd, double r1[], double r2[], double dr[] )

/******************************************************************************/
/*
  Purpose:

    DIST computes the displacement (and its norm) between two particles.

  Modified:

    21 November 2007

  Author:

    Bill Magro, Kuck and Associates, Inc.
    C version by John Burkardt

  Parameters:

    Input, int ND, the number of spatial dimensions.

    Input, double R1[ND], R2[ND], the positions of the particles.

    Output, double DR[ND], the displacement vector.

    Output, double D, the Euclidean norm of the displacement.
*/
{
  double d;
  int i;

  d = 0.0;
  for ( i = 0; i < nd; i++ )
  {
    dr[i] = r1[i] - r2[i];
    d = d + dr[i] * dr[i];
  }
  d = sqrt ( d );

  return d;
}
/******************************************************************************/

void initialize ( int np, int nd, double box[], int *seed, double pos[], 
  double vel[], double acc[] )

/******************************************************************************/
/*
  Purpose:

    INITIALIZE initializes the positions, velocities, and accelerations.

  Modified:

    21 November 2007

  Author:

    Bill Magro, Kuck and Associates, Inc.
    C version by John Burkardt

  Parameters:

    Input, int NP, the number of particles.

    Input, int ND, the number of spatial dimensions.

    Input, double BOX[ND], specifies the maximum position
    of particles in each dimension.

    Input, int *SEED, a seed for the random number generator.

    Output, double POS[ND*NP], the position of each particle.

    Output, double VEL[ND*NP], the velocity of each particle.

    Output, double ACC[ND*NP], the acceleration of each particle.
*/
{
  int i;
  int j;
/*
  Give the particles random positions within the box.
*/
  for ( i = 0; i < nd; i++ )
  {
    for ( j = 0; j < np; j++ )
    {
      pos[i+j*nd] = box[i] * r8_uniform_01 ( seed );
    }
  }

  for ( j = 0; j < np; j++ )
  {
    for ( i = 0; i < nd; i++ )
    {
      vel[i+j*nd] = 0.0;
    }
  }
  for ( j = 0; j < np; j++ )
  {
    for ( i = 0; i < nd; i++ )
    {
      acc[i+j*nd] = 0.0;
    }
  }
  return;
}
/******************************************************************************/

double r8_uniform_01 ( int *seed )

/******************************************************************************/
/*
  Purpose:

    R8_UNIFORM_01 is a unit pseudorandom R8.

  Discussion:

    This routine implements the recursion

      seed = 16807 * seed mod ( 2**31 - 1 )
      unif = seed / ( 2**31 - 1 )

    The integer arithmetic never requires more than 32 bits,
    including a sign bit.

  Modified:

    11 August 2004

  Author:

    John Burkardt

  Reference:

    Paul Bratley, Bennett Fox, Linus Schrage,
    A Guide to Simulation,
    Springer Verlag, pages 201-202, 1983.

    Bennett Fox,
    Algorithm 647:
    Implementation and Relative Efficiency of Quasirandom
    Sequence Generators,
    ACM Transactions on Mathematical Software,
    Volume 12, Number 4, pages 362-376, 1986.

  Parameters:

    Input/output, int *SEED, a seed for the random number generator.

    Output, double R8_UNIFORM_01, a new pseudorandom variate, strictly between
    0 and 1.
*/
{
  int k;
  double r;

  k = *seed / 127773;

  *seed = 16807 * ( *seed - k * 127773 ) - k * 2836;

  if ( *seed < 0 )
  {
    *seed = *seed + 2147483647;
  }

  r = ( double ) ( *seed ) * 4.656612875E-10;

  return r;
}
/******************************************************************************/

void timestamp ( void )

/******************************************************************************/
/*
  Purpose:

    TIMESTAMP prints the current YMDHMS date as a time stamp.

  Example:

    31 May 2001 09:45:54 AM

  Modified:

    24 September 2003

  Author:

    John Burkardt

  Parameters:

    None
*/
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  size_t len;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  len = strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  printf ( "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}
/******************************************************************************/

void update ( int np, int nd, double pos[], double vel[], double f[], 
  double acc[], double mass, double dt )

/******************************************************************************/
/*
  Purpose:

    UPDATE updates positions, velocities and accelerations.

  Discussion:

    The time integration is fully parallel.

    A velocity Verlet algorithm is used for the updating.

    x(t+dt) = x(t) + v(t) * dt + 0.5 * a(t) * dt * dt
    v(t+dt) = v(t) + 0.5 * ( a(t) + a(t+dt) ) * dt
    a(t+dt) = f(t) / m

  Modified:

    21 November 2007

  Author:

    Bill Magro, Kuck and Associates, Inc.
    C version by John Burkardt

  Parameters:

    Input, int NP, the number of particles.

    Input, int ND, the number of spatial dimensions.

    Input/output, double POS[ND*NP], the position of each particle.

    Input/output, double VEL[ND*NP], the velocity of each particle.

    Input, double F[ND*NP], the force on each particle.

    Input/output, double ACC[ND*NP], the acceleration of each particle.

    Input, double MASS, the mass of each particle.

    Input, double DT, the time step.
*/
{
  int i;
  int j;
  double rmass;

  rmass = 1.0 / mass;
//long long flpins;
  //int retval,Events[2]= {PAPI_TOT_CYC, PAPI_TOT_INS};
  //long_long values[2];

/*
 if (PAPI_start_counters (Events, 2) != PAPI_OK) {
    printf("Error starting counters\n");
    exit(1);
  }


# pragma omp parallel for default ( shared ) private ( i, j )*/
  for ( j = 0; j < np; j++ )
  {
    for ( i = 0; i < nd; i++ )
    {
      pos[i+j*nd] = pos[i+j*nd] + vel[i+j*nd] * dt + 0.5 * acc[i+j*nd] * dt * dt;
      vel[i+j*nd] = vel[i+j*nd] + 0.5 * dt * ( f[i+j*nd] * rmass + acc[i+j*nd] );
      acc[i+j*nd] = f[i+j*nd] * rmass;
    }
  }


/*if (PAPI_stop_counters (values, 2) !=  PAPI_OK) {
    printf("Error stopping counters\n");
    exit(1);
  }

  printf("PAPI_TOT_CYC = %lld\n", values[0]);
  printf("PAPI_TOT_INS_3 = %lld\n", values[1]);*/


  return;
}

