#include "ecc.h"


/**
 * @brief Prime Field (BIGNUM) Point Addition (Basic)
 * @details
 * - 
 * @param[out] EC_GF2N_PNT *R 
 * @param[in] EC_GF2N_PNT *P 
 * @param[in] EC_GF2N_PNT *Q 
 * @date 2017. 06. 05. \n
 */
void EC_BN_Pnt_Add(EC_GF2N_PNT *R, EC_GF2N_PNT *P, EC_GF2N_PNT *Q)
{
    //if P, Q is point at infinity
    //



}

/**
 * @brief Prime Field (BIGNUM) Point Doubling (Basic)
 * @details
 * - 
 * @param[out] EC_GF2N_PNT *R 
 * @param[in] EC_GF2N_PNT *P 
 * @date 2017. 06. 05. \n
 */
void EC_BN_Pnt_Dbl()
{


}

/**
 * @brief Binary Field (GF2N) Point Addition (Basic)
 * @details
 * - 
 * @param[out] EC_GF2N_PNT *R 
 * @param[in] EC_GF2N_PNT *P 
 * @param[in] EC_GF2N_PNT *Q 
 * @date 2017. 06. 05. \n
 */
void EC_GF2N_Pnt_Add()
{


}



/**
 * @brief Binary Field (GF2N) Point Doubling (Basic)
 * @details
 * - 
 * @param[out] EC_GF2N_PNT *R 
 * @param[in] EC_GF2N_PNT *P 
 * @date 2017. 06. 05. \n
 */
void EC_GF2N_Pnt_Dbl()
{


}


/**
 * @brief Prime Field (BIGNUM) Point Doubling (Basic)
 * @details
 * - 한참 미완성... BN 부터 고쳐야 함...
 * @param[out] EC_BN_PNT *R 
 * @param[in] EC_BN_PNT *P 
 * @date 2017. 06. 05. \n
 */
void EC_BN_Pnt_Dbl_Jac(EC_BN_PNT *R, EC_BN_PNT *P)
{
    BIGNUM T1, T2;

    //if (P is Point at infinity) -> return P = Point at infinity
    
    BN_Sqr_Mod(T1, P->Z, N);            //  2. T1 <- (Z1)^2
    BN_Sub_Mod(T2, P->X, T1, N);        //  3. T2 <- X1 - T1
    BN_Add_Mod(T1, P->X, T1, N);        //  4. T1 <- X1 + T1
    BN_Mul_Mod(T2, T2, T1, N);          //  5. T2 <- T2 * T1
    // 6. T2 = 3*T3                     //  6. T2 <- 3 * T2
    // 7. R->Y = 3*T3                   //  7. Y3 <- 2 * Y1
    BN_Mul_Mod(R->Z, R->Y, P->Z, N);    //  8. Z3 <- Y3 * Z1
    BN_Sqr_Mod(R->Y, R->Y, N);          //  9. Y3 <- (Y3)^2
                                        // 10. T3 <- Y3 * X1
                                        // 11. Y3 <- (Y3)^2
                                        // 12. Y3 <- Y3 / 2
                                        // 13. X3 <- (T2)^2
                                        // 14. T1 <- 2 * T3
                                        // 15. X3 <- X3 - T1
                                        // 16. T1 <- T3 - X3
                                        // 17. T1 <- T1 * T2
                                        // 18. Y3 <- T1 - Y3
                                        // 19. Return (X3, Y3, Z3)

}


/**
 * @brief Prime Field (BIGNUM) Point Doubling (Basic)
 * @details
 * - 한참 미완성... GF2N 부터 고쳐야 함...
 * @param[out] EC_BN_PNT *R 
 * @param[in] EC_BN_PNT *P 
 * @param[in] EC_BN_PNT *Q 
 * @date 2017. 06. 05. \n
 */
void EC_BN_Pnt_Add_Aff_Jac(EC_BN_PNT *R, EC_BN_PNT *P, EC_BN_PNT *Q)
{
    BIGNUM T1, T2, T3, T4;

    //if (P is Point at infinity) -> return P = Point at infinity
                                        //  1. if Q = infinity -> return (X1, Y1, Z1)
                                        //  2. if P = infinity -> return (x2, y2)
                                        //  3. T1 <- (Z1)^2
                                        //  4. T2 <- T1 * Z1
                                        //  5. T1 <- T1 * x2
                                        //  6. T2 <- T2 * y2
                                        //  7. T1 <- T1 - X1
                                        //  8. T2 <- T2 - Y1
                                        //  9. if T1 = 0 -> ...
                                        // 10. Z3 <- Z1 * T1
                                        // 11. T3 <- (T1)^2
                                        // 12. T4 <- T3 * T1
                                        // 13. T3 <- T3 * X1
                                        // 14. T1 <- 2 * T3
                                        // 15. X3 <- (T2)^2
                                        // 16. X3 <- X3 - T1
                                        // 17. X3 <- X3 - T4
                                        // 18. T3 <- T3 - X3
                                        // 19. T3 <- T3 * T2
                                        // 20. T4 <- T4 * Y1
                                        // 21. Y3 <- T3 - T4
                                        // 22. return (X3, Y3, Z3)

}


/**
 * @brief Binary Field (GF2N) Point Doubling (LDCoordinates)
 * @details
 * - 한참 미완성... GF2N 부터 고쳐야 함...
 * @param[out] EC_GF2N_PNT *R 
 * @param[in] EC_GF2N_PNT *P 
 * @date 2017. 06. 05. \n
 */
void EC_BN_Pnt_Dbl_LD(EC_GF2N_PNT *R, EC_GF2N_PNT *P)
{
    GF2N T1, T2;


                                            //  1. if P = infinity -> return P = infinity
                                            //  2. T1 <- (Z1)^2
                                            //  3. T2 <- (X1)^2
                                            //  4. Z3 <- T1 * T2
                                            //  5. X3 <- (T2)^2
                                            //  6. T1 <- (T1)^2
                                            //  7. T2 <- T1 * b
                                            //  8. X3 <- X3 + T2
                                            //  9. T1 <- (Y1)^2
                                            // 10. if a = 1 -> T1 <- T1 + T3
                                            // 11. T1 <- T1 + T2
                                            // 12. Y3 <- X3 * T1
                                            // 13. T1 <- T2 * Z3
                                            // 14. Y3 <- Y3 + T1
                                            // 15. return (X3, Y3, Z3)
                                            
}

/**
 * @brief Binary Field (GF2N) Point Doubling (LD-Affine Coordinates)
 * @details
 * - 한참 미완성... GF2N 부터 고쳐야 함...
 * @param[out] EC_GF2N_PNT *R 
 * @param[in] EC_GF2N_PNT *P 
 * @param[in] EC_GF2N_PNT *Q 
 * @date 2017. 06. 05. \n
 */
void EC_GF2N_Pnt_Add_LD_Aff(EC_GF2N_PNT *R, EC_GF2N_PNT *P, EC_GF2N_PNT *Q)
{
    BIGNUM T1, T2, T3, T4;
    
                                        //  1. if Q = infinity -> return (X1, Y1, Z1)
                                        //  2. if P = infinity -> return (x2, y2)
                                        //  3. T1 <- Z1 * x2
                                        //  4. T2 <- (Z1)^2
                                        //  5. X3 <- X1 + T1
                                        //  6. T1 <- Z1 * X3
                                        //  7. T3 <- T2 * y2
                                        //  8. Y3 <- Y1 + T3
                                        //  9. if X3 = 0 ->
                                        // 10. Z3 <- (T1)^2
                                        // 11. T3 <- T1 * Y3
                                        // 12. if a = 1 -> T1 <- T1 + T2
                                        // 13. T2 <- (X3)^2
                                        // 14. X3 <- T2 * T1
                                        // 15. T2 <- (Y3)^2
                                        // 16. X3 <- X3 + T2
                                        // 17. X3 <- X3 + T3
                                        // 18. T2 <- x2 * Z3
                                        // 19. T2 <- T2 + X3
                                        // 20. T1 <- (Z3)^2
                                        // 21. T3 <- T3 + Z3
                                        // 22. Y3 <- T3 * T2
                                        // 23. T2 <- x2 + y2
                                        // 24. T3 <- T1 * T2
                                        // 25. Y3 <- Y3 + T3
                                        // 26. return (X3, Y3, Z3)

}

/**
 * @brief Point Multiplication of Prime Field (Left-to-Right Binary Method)
 * @details
 * - 한참 미완성...
 * @param[out] EC_BN_PNT *R 
 * @param[in] EC_BN_PNT *P
 * @param[in] SNINT k
 * @date 2017. 06. 05. \n
 */
void EC_BN_Pnt_Mul(EC_BN_PNT *R, EC_BN_PNT *P, SNINT k)
{
    EC_BN_PNT Q;

    // Q init (infinity)

    // P : Aff -> Jac 변환
    // k -> binary 변환
    for(i = t - 1 ; i > 0 ; i--)
    {
        EC_BN_Pnt_Dbl_Jac(Q, Q);
        if(k_i == 1)
            EC_BN_Pnt_Add_Aff_Jac(Q, P, Q);
    }
    EC_BN_Copy(R, Q);
}

/**
 * @brief Point Multiplication of Binary Field (Left-to-Right Binary Method)
 * @details
 * - 한참 미완성...
 * @param[out] EC_GF2N_PNT *R 
 * @param[in] EC_GF2N_PNT *P
 * @param[in] SNINT k
 * @date 2017. 06. 05. \n
 */
void EC_GF2N_Pnt_Mul(EC_GF2N_PNT *R, EC_GF2N_PNT *P, SNINT k)
{
    EC_GF2N_PNT Q;

    // Q init (infinity)

    // P : Aff -> LD 변환
    // k -> binary 변환
    for(i = t - 1 ; i > 0 ; i--)
    {
        EC_GF2N_Pnt_Dbl_LD(Q, Q);
        if(k_i == 1)
            EC_GF2N_Pnt_Add_LD_Aff(Q, Q, P);
    }
    EC_GF2N_Copy(R, Q);
}