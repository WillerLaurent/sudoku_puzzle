#include <stdio.h>
#include <stdlib.h>

void	affichage(int grille[9][9])
{
	int i; 
	int j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			printf(((j + 1) % 3) ? "%d " : "%d|", grille[i][j]);
			j++;
		}
		printf("\n");
		if ((i + 1) % 3 == 0)
			printf("------------------\n");
		i++;
	}
	printf("\n\n");
}

int test_row(int grille[9][9], int i, int k)
{
	int j;

	j = 0;
	while (j < 9)
	{
		if (grille[i][j] == k)
			return (0);
		j++;
	}
	return (1);
}

int test_colomn(int grille[9][9], int j, int k)
{
	int i;

	i = 0;
	while (i < 9)
	{
		if (grille[i][j] == k)
			return (0);
		i++;
	}
	return (1);
}

int test_bloc(int grille[9][9], int i, int j, int k)
{
	int bloc_i;
	int bloc_j;

	bloc_i = i - (i % 3);
	bloc_j = j - (j % 3);
	i = bloc_i;
	while (i < bloc_i + 3)
	{
		j = bloc_j;
		while (j < bloc_j + 3)
		{
			if (grille[i][j] == k)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int is_valide(int grille[9][9], int position)
{
	/*si on est à la 82e case, on sort*/
	if (position == 9 * 9)
		return (1);
	/*on récupère les coordonnées de la position*/
	int i;
	int j;

	i = position / 9;
	j = position % 9;

	/*si la case n'est pas vide, on passe à la suivante (appel récursif)*/
	if (grille[i][j] != 0)
		return (is_valide(grille, position + 1));

	/*énumération des valeurs possibles */
	int k;

	k = 1;
	while (k <= 9)
	{
		/*si la valeur est absente, donc autorisée*/
		if (test_row(grille, i, k) && test_colomn(grille, j, k) &&
				test_bloc(grille, i, j , k))
		{
		affichage(grille);
		printf("position = %d, k = %d\n", position, k);
			/*on enregistre k dans la grille*/
			grille[i][j] = k;

			/* on appelle récursivement la fonction is_valide pour
			 * voir si ce choix est bon pour la suite*/
			if (is_valide(grille, position + 1))
			{
				printf("return 1 : position = %d, k = %d\n", position, k);
					return (1);
			}
					/*si la valeur est bonne plus la peine
					 * de continuer, on renvoie TRUE*/
		}
		k++;
	}
	/*tous les chiffres ont été testés, aucun n'est bon, 
	 * on réinitialise la case*/
	grille[i][j] = 0;
	printf("return 0 : position = %d, k = %d\n", position, k);
	/* puis on retourne false*/
	return (0);
}

int main(void)
{
	int grille[9][9] =
	{
		{9,0,0,1,0,0,0,0,5},
		{0,0,5,0,9,0,2,0,1},
		{8,0,0,0,4,0,0,0,0},
		{0,0,0,0,8,0,0,0,0},
		{0,0,0,7,0,0,0,0,0},
		{0,0,0,0,2,6,0,0,9},
		{2,0,0,3,0,0,0,0,6},
		{0,0,0,2,0,0,9,0,0},
		{0,0,1,9,0,4,5,7,0}
	};

	printf("grille avant :\n");
	affichage(grille);
	is_valide(grille, 0);

	printf("grille apres : \n");
	affichage(grille);


}
