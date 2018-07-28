#define TAKEOFFCOUNT    5000
#define SLOWUPCOUNT     30000
#define SLOWDOWNCOUNT   20000
#define HIGHDC          57
#define LOWDC           37
#define HOVTIME         6


int thro_dc = 35;
int aile_dc = 48;
int elev_dc = 49;
int thro_dcCount = 0;
int aile_dcCount = 0;
int elev_dcCount = 0;
int secondCount = 0;
int timeCount = 0;
int holdCount = 0;
int warning = 0;

int i = 0;
int state = 0; 
int trigger[5] = {0,0,0,0,0};
int triggerState = 0;
unsigned int flex[2] = {0};
unsigned int flex1 = 0;
unsigned int flex2 = 0;
unsigned int distance = 0;

void Setup_Timer(void);