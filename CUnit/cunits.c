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

void test_verifier_placement() {
   int taille_plateau = 5;
   char **plateau = allouer_plateau(taille_plateau);

   Case debut = {0, 0};
   int taille_bateau = 3;
   CU_ASSERT_TRUE(verifier_placement(plateau, debut, taille_bateau, 0, taille_plateau));
   debut.x = 4;
   CU_ASSERT_FALSE(verifier_placement(plateau, debut, taille_bateau, 1, taille_plateau));

   for (int i = 0; i < taille_plateau; i++) {
      free(plateau[i]);
   }
   free(plateau);
}

void test_valider_taille() {
   CU_ASSERT_TRUE(valider_taille(TAILLE_MIN_PLATEAU));
   CU_ASSERT_TRUE(valider_taille(TAILLE_MAX_PLATEAU));
   CU_ASSERT_FALSE(valider_taille(TAILLE_MIN_PLATEAU - 1));
   CU_ASSERT_FALSE(valider_taille(TAILLE_MAX_PLATEAU + 1));
}

int main() {
   CU_initialize_registry();

   CU_pSuite suite1 = CU_add_suite("Plateau Allocation Test", NULL, NULL);
   CU_add_test(suite1, "test_allouer_plateau", test_allouer_plateau);

   CU_pSuite suite2 = CU_add_suite("Vérification Placement Test", NULL, NULL);
   CU_add_test(suite2, "test_verifier_placement", test_verifier_placement);

   CU_pSuite suite3 = CU_add_suite("Suite de Validation Taille Plateau", NULL, NULL);
   CU_add_test(suite3, "test_valider_taille", test_valider_taille);

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();

   CU_cleanup_registry();
   return 0;
}
