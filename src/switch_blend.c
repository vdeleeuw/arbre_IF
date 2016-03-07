#include "switch_blend.h"

GLuint switch_blend(GLuint blend) {
  blend = blend ? 0 : 1;              // switch the current value of blend, between 0 and 1.
  if (!blend) {
    glDisable(GL_BLEND);              // Turn Blending Off
    glEnable(GL_DEPTH_TEST);          // Turn Depth Testing On
  } else {
    glEnable(GL_BLEND);		    	// Turn Blending On
    glDisable(GL_DEPTH_TEST);         // Turn Depth Testing Off
  }
  return blend;
}
