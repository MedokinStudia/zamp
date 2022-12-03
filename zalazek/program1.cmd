#define MACRO 60
#define MACRO2 70
#define MACRO3 80

 

Begin_Parallel_Actions
Rotate Podstawa 5 Z 180  
Rotate Podstawa.Ramie1 2 Y 20  
End_Parallel_Actions

Begin_Parallel_Actions
Rotate Podstawa.Ramie1.Ramie2 2 Z 45  
Rotate Podstawa.Ramie1 2 Y 20  
End_Parallel_Actions

Begin_Parallel_Actions
Rotate Kadlub.przod.piasta.prop 50 Y 2000 
End_Parallel_Actions

Begin_Parallel_Actions
Rotate Kadlub.przod.piasta.prop 120 Y 6000
Move Kadlub 0.2  10
End_Parallel_Actions
