#include <stdio.h>
#include "tk.h"

/* this file contains example code for interfacing GL to Tcl. The 
   functions here do app-specific initialization, inform the interpreter
   about app commands, and provide "wrapper" functions for calling
   GL from Tcl. */


extern int 
  torus_render_cmd(), 
  torus_init_cmd(), 
  torus_finish_cmd(), 
  torusSet_cmd(), 
  torus_init_cmd();


/* ARGSUSED */
torus_tcl_init(interp, w)
     Tcl_Interp *interp;
     Tk_Window w;
{
  /* Called from "glxwish" to initialize app-specific Tcl commands.
     Each app will have a different set of commands. 
   */

  Tcl_CreateCommand(interp, "gl-render", torus_render_cmd, NULL, NULL);
  Tcl_CreateCommand(interp, "gl-init", torus_init_cmd, NULL, NULL);
  Tcl_CreateCommand(interp, "gl-finish", torus_finish_cmd, NULL, NULL);
  Tcl_CreateCommand(interp, "gl-param", torusSet_cmd, NULL, NULL);
  torus_var_init();
}  

/* ARGSUSED */
int torus_render_cmd(dummy, interp, argc, argv)
    ClientData dummy;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
  /* one render  */
  torus_render();
  return(TCL_OK);
}


/* ARGSUSED */
int torus_init_cmd(dummy, interp, argc, argv)
    ClientData dummy;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
  torus_init();
  return(TCL_OK);
}

/* ARGSUSED */
int torus_finish_cmd(dummy, interp, argc, argv)
    ClientData dummy;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
  /* one render  */
  torus_finish();
  return(TCL_OK);
}


/* ARGSUSED */
int
torusSet_cmd(dummy, interp, argc, argv)
    ClientData dummy;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
  /* useful for setting variables in your GL program */

  /* get */
  if (argc == 2){
    if(torusSet(argv[1], interp->result, 0) != 0){
      Tcl_AppendResult(interp, 
		       "bad param name \"", argv[1], "\"", (char *) NULL);
      return(TCL_ERROR);
    }

    return(TCL_OK);
  }

  /* set */
  else if (argc == 3){
    if(torusSet(argv[1], argv[2], 1) != 0){
      Tcl_AppendResult(interp, 
		       "bad param name \"", argv[1], "\"", (char *) NULL);
      return(TCL_ERROR);
    }
    return(TCL_OK);
  }

  else {
    Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
		     " param val\"", (char *) NULL);
    return(TCL_ERROR);
  }
}
