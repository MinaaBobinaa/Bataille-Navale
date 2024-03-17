#include "../include/jeu.h"
#include "../include/stats.h"
#include <stdio.h>
#include <stdlib.h>

#include <CUnit/Basic.h>




void test_allouer_plateau() {
    int taille = 5;
    char **plateau = allouer_plateau(taille);    
    CU_ASSERT_PTR_NOT_NULL(plateau);

    for (int i = 0; i < taille; i++) {
        CU_ASSERT_PTR_NOT_NULL(plateau[i]);
        for (int j = 0; j < taille; j++) {
            CU_ASSERT_EQUAL(plateau[i][j], '.');
        }
    }

    for (int i = 0; i < taille; i++) {
        free(plateau[i]);
    }
    free(plateau);
}

/**
* Attention, il faut absolument avoir une fonction main pour pouvoir effectuer les tests
* En voici une pour l'exemple avec les tests qui sont fait.
* Je vous laisse donc aller faire des recherches supplementaires la dessus.
* N'hesitez pas a faire man cunit pour chercher les assertions interessantes pour vos tests
*/
int main() {
    CU_initialize_registry();

    CU_pSuite suite2 = CU_add_suite("Plateau Allocation Test", NULL, NULL);
    CU_add_test(suite2, "test_allouer_plateau", test_allouer_plateau);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return 0;
}
