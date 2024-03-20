#include "../include/jeu.h"
#include "../include/stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>

void test_commencer_jeu() {
   commencer_jeu();
   CU_PASS("commencer_jeu called successfully.");
}

void test_menu() {
   menu();
   CU_PASS("menu called successfully.");
}

void test_terminer_jeu() {
   int tirs_test = 10;
   terminer_jeu(tirs_test);
   CU_PASS("terminer_jeu called successfully.");
}

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

void test_free_plateau() {
   int taille = 5;
   char **plateau = allouer_plateau(taille); 
    
   CU_ASSERT_PTR_NOT_NULL_FATAL(plateau);
   for (int i = 0; i < taille; i++) {
      CU_ASSERT_PTR_NOT_NULL_FATAL(plateau[i]);
   }

   free_plateau(plateau, taille);
   CU_PASS("free_plateau executed without segmentation faults.");
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

void test_placer_navire() {
   int taille_plateau = 10;
   char **plateau = allouer_plateau(taille_plateau);
   Navire navire = {.taille = 3, .nom = "Destroyer",
      .touche = 0, .nbr_lettres = 9 
   };
   placer_navire(plateau, &navire, taille_plateau);
   CU_PASS("placer_navire called successfully.");

   for (int i = 0; i < taille_plateau; i++) {
      free(plateau[i]);
   }
   free(plateau);
}

void test_affichage_plateau() {
   int taille = 6;
   char **plateau = allouer_plateau(taille);

   affichage_plateau(plateau, taille);
   CU_PASS("affichage_plateau called successfully.");

   for (int i = 0; i < taille; i++) {
      free(plateau[i]);
   }
   free(plateau);
}

void test_gerer_touche() {
   Navire navire = {
      .taille = 3, .nom = "Destroyer",
      .touche = 0, .nbr_lettres = 9
   };
   GameStats stats = {
      .nbr_lettres = 0, .premier_touche = 0,
      .coups_touche = 0
   };
   gerer_touche(&navire, &stats);
   CU_ASSERT_EQUAL(navire.touche, 1);
   CU_ASSERT_EQUAL(stats.nbr_lettres, navire.nbr_lettres);
}

void test_gerer_navire_coule() {
   int taille_plateau = 6; 
   char **plateau = allouer_plateau(taille_plateau); 
   char **action_plateau = allouer_plateau(taille_plateau);
   int navire_coule = 0;
   Navire navire = {.taille = 3, .nom = "Destroyer",
      .positions = {{1, 1}, {1, 2}, {1, 3}},
   };
   GameStats stats = {
      .dernier_navire = "",
   };

   gerer_navire_coule(&navire, plateau, action_plateau, &navire_coule, &stats);
   CU_ASSERT_EQUAL(navire_coule, 1);
   free_plateau(plateau, taille_plateau);
   free_plateau(action_plateau, taille_plateau); 
}

void test_touche_navire() {
   int taille_plateau = 6; 
   char **plateau = allouer_plateau(taille_plateau); 
   char **action_plateau = allouer_plateau(taille_plateau);
   int navire_coule = 0;

   Navire navire = {
      .taille = 3, .nom = "Destroyer",
      .positions = {{1, 1}, {1, 2}, {1, 3}}, .touche = 0,
   };
   GameStats stats = {
      .dernier_navire = "",
   };

   touche_navire(&navire, 1, 1, plateau, action_plateau, &navire_coule, &stats);
   CU_ASSERT_EQUAL(navire.touche, 1);
   free_plateau(plateau, taille_plateau);
   free_plateau(action_plateau, taille_plateau);
}

void test_valider_taille() {
   CU_ASSERT_TRUE(valider_taille(TAILLE_MIN_PLATEAU));
   CU_ASSERT_TRUE(valider_taille(TAILLE_MAX_PLATEAU));
   CU_ASSERT_FALSE(valider_taille(TAILLE_MIN_PLATEAU - 1));
   CU_ASSERT_FALSE(valider_taille(TAILLE_MAX_PLATEAU + 1));
}

void test_initialiser_jeu() {
   int taille = 10;
   char **plateau = NULL;
   char **action_plateau = NULL;
   Navire navires[5] = {};

   initialiser_jeu(taille, &plateau, &action_plateau, navires);
   CU_ASSERT_PTR_NOT_NULL_FATAL(plateau);
   CU_ASSERT_PTR_NOT_NULL_FATAL(action_plateau);
   free_plateau(plateau, taille);
   free_plateau(action_plateau, taille); 
}

void test_verifier_coordonnees_valide() {
   int taille = 10; 
   CU_ASSERT_TRUE(verifier_coordonnees(0, 0, taille));
   CU_ASSERT_TRUE(verifier_coordonnees(5, 5, taille));
   CU_ASSERT_TRUE(verifier_coordonnees(taille-1, taille-1, taille));
}

void test_verifier_coordonnees_invalide() {
   int taille = 10; 
   CU_ASSERT_FALSE(verifier_coordonnees(-1, 0, taille));
   CU_ASSERT_FALSE(verifier_coordonnees(0, -1, taille));
   CU_ASSERT_FALSE(verifier_coordonnees(taille, 0, taille));
   CU_ASSERT_FALSE(verifier_coordonnees(0, taille, taille));
}

void test_proceder_tir_eau() {
   int taille = 5;
   char **plateau = allouer_plateau(taille);
   char **action_plateau = allouer_plateau(taille);
   Navire navires[5]; 
   int tirs = 0, navire_coule = 0;
   GameStats stats = {0};

   proceder_tir(plateau, action_plateau, navires, 0, 0, &tirs, &navire_coule, &stats);
   CU_ASSERT_EQUAL(tirs, 1);
   CU_ASSERT_EQUAL(action_plateau[0][0], 'o');
   CU_ASSERT_EQUAL(stats.coups_eau, 1);
   free_plateau(plateau, taille);
   free_plateau(action_plateau, taille);
}

void test_write_stats_file() {
   GameStats stats;
   init_stats(&stats);
   stats.nbr_total_tirs = 5;
   stats.nbr_lettres = 3;
   stats.coups_eau = 2;
   stats.deja_joue = 0;
   stats.coups_touche = 3;
   strcpy(stats.dernier_navire, "Croiseur");
   stats.premier_touche = 1;

   const char *nomFichierTest = "stats_test_output.txt";
   write_stats_file(&stats, nomFichierTest);
   printf("Les statistiques ont été écrites dans '%s'. Veuillez vérifier ce fichier manuellement.\n", nomFichierTest);
}


int main() {
   CU_initialize_registry();

   CU_pSuite suite1 = CU_add_suite("Jeu Commencement Test", NULL, NULL);
   CU_add_test(suite1, "test_commencer_jeu", test_commencer_jeu);

   CU_pSuite suite2 = CU_add_suite("Menu Test Suite", NULL, NULL);
   CU_add_test(suite2, "test_menu", test_menu);

   CU_pSuite suite3 = CU_add_suite("Terminer Jeu Test Suite", NULL, NULL);
   CU_add_test(suite3, "test_terminer_jeu", test_terminer_jeu);

   CU_pSuite suite4 = CU_add_suite("Plateau Allocation Test", NULL, NULL);
   CU_add_test(suite4, "test_allouer_plateau", test_allouer_plateau);

   CU_pSuite suite6 = CU_add_suite("Libération Plateau Test", NULL, NULL);
   if (suite6 != NULL) {
      CU_add_test(suite6, "test_free_plateau", test_free_plateau);
   }

   CU_pSuite suite7 = CU_add_suite("Vérification Placement Test", NULL, NULL);
   CU_add_test(suite7, "test_verifier_placement", test_verifier_placement);

   CU_pSuite suite8 = CU_add_suite("Suite_8", NULL, NULL);
   CU_add_test(suite8, "Test de placer_navire", test_placer_navire);
  
   CU_pSuite suite9 = CU_add_suite("Suite_9", NULL, NULL);
   CU_add_test(suite9, "Test affichage plateau", test_affichage_plateau);

   CU_pSuite suite10 = CU_add_suite("Suite_10", NULL, NULL);
   CU_add_test(suite10, "Test de gerer_touche", test_gerer_touche);
 
   CU_pSuite suite11 = CU_add_suite("Test gerer_navire_coule", NULL, NULL);
   CU_add_test(suite11, "test gerer_navire_coule", test_gerer_navire_coule);

   CU_pSuite suite12 = CU_add_suite("Test touche_navire", NULL, NULL);
   CU_add_test(suite12, "test touche_navire", test_touche_navire);

   CU_pSuite suite13 = CU_add_suite("Test de Validation Taille Plateau", NULL, NULL);
   CU_add_test(suite13, "test_valider_taille", test_valider_taille);

   CU_pSuite suite14 = CU_add_suite("Test d'Initialization", NULL, NULL);
   CU_add_test(suite14, "test of initialiser_jeu", test_initialiser_jeu);

   CU_pSuite suite15 = CU_add_suite("Suite de test pour verifier_coordonnees", NULL, NULL);
   CU_add_test(suite15, "test avec des coordonnées valides", test_verifier_coordonnees_valide);
   CU_add_test(suite15, "test avec des coordonnées invalides", test_verifier_coordonnees_invalide);

   CU_pSuite suite16 = CU_add_suite("Test proceder_tir", NULL, NULL);
   CU_add_test(suite16, "test de tir dans l'eau", test_proceder_tir_eau);

   CU_pSuite suite17 = CU_add_suite("Suite_Test_Stats", NULL, NULL);
   CU_add_test(suite17, "test_write_stats_file", test_write_stats_file);
  
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();

   CU_cleanup_registry();
   return 0;
}
