#include<stdio.h>
#include<stdlib.h>

main(){

  int *matriz, x_max, y_max, z_max, x, y, z;

  puts("ENTRE COM AS DIMENSOES");
  printf("\nDimensao 1 (X): ");
  scanf("%d", &x_max);
  printf("\nDimensao 2 (Y): ");
  scanf("%d", &y_max);
  printf("\nDimensao 3 (Z):");
  scanf("%d", &z_max);

  matriz = (int *)malloc(x_max*y_max*z_max*sizeof(int));

  if(!matriz) puts("Nao consegui alocar memoria.");
  else{

    for(x = 0; x < x_max; x++)
      for(y = 0; y < y_max; y++)
	for(z = 0; z < z_max; z++)
	  //atribui os valores as posicoes
	  *(matriz + x*(y_max*z_max) + y*(z_max) + z) = (x + y + z);

    for(x = 0; x < x_max; x++)
      for(y = 0; y < y_max; y++)
	for(z = 0; z < z_max; z++)
	  //exibe os valores das posicoes
	  printf("\n%d+%d+%d=%2d", x, y, z, *(matriz + x*(y_max*z_max) + y*(z_max) + z));
  }

  free(matriz);

}
