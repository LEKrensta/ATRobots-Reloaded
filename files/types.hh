#ifndef __TYPES_HH__
#define __TYPES_HH__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

//constant variables
const char progname[] = "AT-Robots";
const char version[] = "2.11";
const char cnotice1[] = "Copyright 1997 ''99, Ed T. Toton III";
const char cnotice2[] = "All Rights Reserved.";
const char cnotice3[] = "Copyright 2014, William 'Amos' Confer";
const char main_name[] = "ATR2";
const char robot_ext[] = ".AT2";
const char locked_ext[] = ".ATL";
const char config_ext[] = ".ATS";
const char compile_ext[] = ".CMP";
const char report_ext[] = ".REP";
const bool _T = true;
const bool _F = false;
const int minint = -32768; 
//debugging/compiler
const bool show_code = _F;
const bool compile_by_line = _F;
const int max_var_len = 16;
const bool debugging_compiler = _F;
//robots
const int max_robots = 31; //starts at 0, so total is max_robots+1
const int max_code = 1023;
const int max_op = 3;
const int stack_size = 256;
const int stack_base = 768;
const int max_ram = 1023; //but this does start at 0 (odd #, 2^n-1)
const int max_vars = 256;
const int max_labels = 256;
const int acceleration = 4;
const int turn_rate = 8;
const int max_vel = 4;
const int max_missiles = 1023;
const int missile_spd = 32;
const int hit_range = 14;
const int blast_radius = 25;
const int crash_range = 8;
const int max_sonar = 250;
const int com_queue = 512;
const int max_queue = 255;
const int max_config_points = 12;
const int max_mines = 63;
const int mine_blast = 35;
const int max_robot_lines = 8;
//Simulator and graphic

const float screen_scale = 0.46;
const int screen_x = 5;
const int screen_y = 5;
const int robot_scale = 6;
const int default_delay = 20;
const int default_slice = 5;
const double mine_circle = trunc(mine_blast * screen_scale) + 1; // Trunc is in the math lib... kinda like rounding
const double blast_circle = trunc(blast_radius * screen_scale) + 1;
const int mis_radius = trunc(hit_range/2) + 1;
/**=======SDL========
 Gray50 : FillPatternType = ($AA, $55, $AA, $55,
                             $AA, $55, $AA, $55);
**/

/* OPERATOR RECORD */
typedef struct{
    int op[max_op];
} op_rec;

/* PROGRAM TYPE */
typedef op_rec prog_type[max_code];

/* CONFIG RECORD */
typedef struct{
    int scanner,
        weapon,
        armor,
        engine,
        heatsinks,
        shield,
        mines;
} config_rec;

/* MINE RECORD */
typedef struct{
    double x,
           y;
    int detect,
        yield;
    bool detonate;
} mine_rec;

/* ROBOT RECORD */
typedef struct{
    double x,
        y,
        lx,
        ly,
        xv,
        yv,
        speed,
        shotstrength,
        damageadj,
        speedadj,
        meters;

    int hd,
        thd,
        lhd,
        spd,
        tspd,
        armor,
        larmor,
        heat,
        lheat,
        ip,
        plen,
        scanarc,
        accuracy,
        shift,
        err,
        delay_left,
        robot_time_limit,
        max_time,
        time_left,
        lshift,
        arc_count,
        sonar_count,
        scanrange,
        last_damage,
        last_hit,
        transponder,
        shutdown,
        channel,
        lendarc,
        endarc,
        lstartarc,
        startarc,
        mines,
        mem_watch;

    int tx[max_robot_lines],
        ltx[max_robot_lines],
        ty[max_robot_lines],
        lty[max_robot_lines],
        ram[max_ram];
        mine_rec mine[max_mines];

    long wins,
         trials,
         kills,
         deaths,
         startkills,
         shots_fired,
         match_shots,
         hits,
         damage_total,
         cycles_lived,
         error_count;

    char   *name;
    char   *fn;

    bool is_locked,
         shields_up,
         lshields,
         overburn,
         keepshift,
         cooling,
         won;

        /* FILE POINTER */
        //FILE * errorlog;
        ofstream errorlog; //change to file stream //FILE * errorlog
        config_rec config;
        prog_type code;

} robot_rec;

/* PARSEING TYPE */
typedef char parsetype[max_op+1][16+1];

/* ROBOT POINTER */
typedef robot_rec* robot_ptr;

/* MISSLE RECORD */
typedef struct{
    double x,
           y,
           lx,
           ly,
           mult,
           mspd;

    int    source,
           a,
           hd,
           rad,
           lrad,
           max_rad;
} missile_rec;

//Variables
//robot var
static int num_robots;
static robot_ptr * robot = (robot_ptr *)malloc(sizeof(robot_ptr)*(max_robots-(-2)+1));
static missile_rec missile[max_missiles+1]; //+1
//compiler variable
static FILE * f; //Needs to see where this is used //Parse_param creates another one //****
static int numvars, numlabels, maxcode, lock_pos, lock_dat;
static char varname [1+max_vars][1+max_var_len];
static int varloc[1+max_vars];
static char labelname [1+max_vars][1+max_var_len];
static int labelnum[1+max_labels];
static bool show_source, compile_only;
static char * lock_code;
 //simulator/graphics variable
static bool bout_over;
static int step_mode;
static int temp_mode;
static int step_count;
static bool step_loop;
 //bool show_debugger;
static bool old_shields, insane_missiles, debug_info, windoze, no_gfx, logging_errors, timing, show_arcs;
static int game_delay, time_slice, insanity, update_timer, max_gx, max_gy, stats_mode;
static long game_limit, game_cycle;
static long matches, played, executed;
//general settings
static bool quit, report, show_cnotice;
static int kill_count, report_type;
//read & write stats
static size_t pos = 0;
static string line;
static string token;

static string tempFile = "tempFile.AT2";
static string delimiter = "=";

static string scanner = "#CONFIG scanner",
       weapon = "#CONFIG weapon",
       armor = "#CONFIG armor",
       engine = "#CONFIG engine",
       heatsinks = "#CONFIG heatsinks",
       mines = "#CONFIG mines",
       shield = "#CONFIG shield";

static string scannerVal,
       weaponVal,
       armorVal,
       engineVal,
       heatsinksVal,
       minesVal,
       shieldVal;
       
static int    numScannerVal;
static int    numWeaponVal;
static int    numEngineVal;
static int    numArmorVal;
static int    numHeatsinksval;
static int    numMinesVal;
static int    numShieldVal;

#endif
