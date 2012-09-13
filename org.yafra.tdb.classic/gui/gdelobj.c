#include <uinclude.h>
#include <ginclude.h>

void gdelobj(
GRAFOBJ *tempObj
)

{
	extern GRAFOBJ *grafObj;
	extern long anzgrafObj;

	GRAFOBJ *akt;

	if (tempObj->text) {
		XtFree((void *)tempObj->text);
	}
	XtFree((void *)tempObj->xpoints);
	XtFree((void *)tempObj->regionPoint);
	for(akt=tempObj; akt-grafObj<anzgrafObj-1; akt++) {
		memcpy((void *)akt, (void *)(akt+1), sizeof(GRAFOBJ));
	}
	anzgrafObj--;
}
