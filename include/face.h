
	/** returns GEMS_TRUE if requires X */
extern int face_uses_X ();

	/** actually execute the 'face' */
extern int face_run (int argc, char **argv);

	/** if an error occurs in the shell or subsystem, the face is
	 * responsible for reporting it. This is the mechanism used.
	 * gems_err refers to the component error (dbi, shell, etc)
	 * subsystem_err is what the component could find out (mysql_error, etc)
	 */
extern void oops (char *gems_err, char *subsystem_err);
