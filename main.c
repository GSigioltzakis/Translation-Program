#include<stdio.h>

/*                          MAIN DOMI TIS ASKISIS

1) xreiazomai 2 stadar sinartiseis: a)tin main()
                                    b)tin sinartisi map pou apothikevo ton pinaka
				    g)tin sinartisi pou epeksergazome ta grammata + FSM

2) xreiazomai X sinartiseis gia kathe periptosi: ντ -> d, ί-> i' kai Λ -> L klp...

3)Ti skillsxreiazomai na ksanathimitho:
    a) to CASE/SWITCH statment
    b) enum types (idk giati)
    c) to I/O system diladi to stdio.h library kai ta functions tou
*/

/* arxizo me to 1b) */
char* translate_char(unsigned char c) {
    /* mapping of ISO8859-7 to ISO8859-1 xrisimopoiodas decimal times */
    static char* MAP[256] = {0};

    static int initialized = 0; /* Flag gia na eimaste sigouri oti tha ta apothikefsoume mia fora */
    static char default_char[2];
    if (!initialized) {
        /* Greek uppercase letters */
        MAP[193] = "A"; /* Α -> A */
        MAP[194] = "V"; /* Β -> B */
        MAP[195] = "G"; /* Γ -> G */
        MAP[196] = "D"; /* Δ -> D */
        MAP[197] = "E"; /* Ε -> E */
        MAP[198] = "Z"; /* Ζ -> Z */
        MAP[199] = "H"; /* Η -> H */
        MAP[200] = "8"; /* Θ -> I */
        MAP[201] = "I"; /* Ι -> I */
        MAP[202] = "K"; /* Κ -> K */
        MAP[203] = "L"; /* Λ -> L */
        MAP[204] = "M"; /* Μ -> M */
        MAP[205] = "N"; /* Ν -> N */
        MAP[206] = "KS"; /* Ξ -> O */
        MAP[207] = "O"; /* Ο -> O */
        MAP[208] = "P"; /* Π -> P */
        MAP[209] = "R"; /* Ρ -> R */
        MAP[210] = "S"; /* Σ -> S */
        MAP[211] = "S"; /* ς -> S (final sigma) */
        MAP[212] = "T"; /* Τ -> T */
        MAP[213] = "Y"; /* Υ -> Y */
        MAP[214] = "F"; /* Φ -> F */
        MAP[215] = "X"; /* Χ -> X */
        MAP[216] = "PS"; /* Ψ -> O */
        MAP[217] = "W"; /* Ω -> O */

        /* Greek lowercase letters */
        MAP[225] = "a"; /* α -> a */
        MAP[226] = "v"; /* β -> v */
        MAP[227] = "g"; /* γ -> g */
        MAP[228] = "d"; /* δ -> d */
        MAP[229] = "e"; /* ε -> e */
        MAP[230] = "z"; /* ζ -> z */
        MAP[231] = "h"; /* η -> i */
        MAP[232] = "8"; /* θ -> i */
        MAP[233] = "i"; /* ι -> i */
        MAP[234] = "k"; /* κ -> k */
        MAP[235] = "l"; /* λ -> l */
        MAP[236] = "m"; /* μ -> m */
        MAP[237] = "n"; /* ν -> n */
        MAP[238] = "ks"; /* ξ -> o */
        MAP[239] = "o"; /* ο -> o */
        MAP[240] = "p"; /* π -> p */
        MAP[241] = "r"; /* ρ -> r */
        MAP[242] = "s"; /* ς -> s (final sigma) */
        MAP[243] = "s"; /* σ -> s */
        MAP[244] = "t"; /* τ -> t */
        MAP[245] = "y"; /* υ -> u */
        MAP[246] = "f"; /* φ -> f */
        MAP[247] = "x"; /* χ -> x */
        MAP[248] = "ps"; /* ψ -> o */
        MAP[249] = "w"; /* ω -> o */


 	/*Greek accented letters */
        MAP[182] = "'A";
	MAP[184] = "'E";
        MAP[185] = "'H";
	MAP[186] = "'I";
        MAP[188] = "'O";
	MAP[190] = "'Y";
	MAP[191] = "'W";

        MAP[220] = "a'";
	MAP[221] = "e'";
	MAP[222] = "h'";
	MAP[223] = "i'";
        MAP[252] = "o'";
	MAP[253] = "y'";
	MAP[254] = "w'";
	/*DIALITIKA*/

	MAP[192] = "i'\"";
	MAP[250] = "i\"";
	MAP[218] = "\"I";

	MAP[224] = "y'\"";
	MAP[251] = "y\"";
	MAP[219] = "\"Y";

        initialized = 1; /* Mark initialization as complete */
    }
    if (MAP[c]) {
        return MAP[c];
    }

    default_char[0] = c;
    default_char[1] = '\0';
    return default_char;
}

typedef enum{
	ANY,
	HAVE_M,
	HAVE_N,
	HAVE_UPPER_N,
        HAVE_UPPER_M,
	HAVE_UPPER_N_LOWER_T,
	HAVE_UPPER_M_LOWER_P
/*	HAVE_ACCENT, GIA TONOUS
	HAVE_DIALITIKA DIALITIKA*/
} State;



/*1g)
	basically we want to create an FSM. How can we do that? by creating enum blcoks for the states and cases to check those cases. We need to
        translate from greek to greeklish, for example: if we type greek a wew get english a OR if we type ν we check he next character ect*/
State process_character(State current, int c) {
    char* translated = translate_char((unsigned char)c);
    switch (current) {
        case ANY:
            if (c == 237 || c == 205) return (c == 237) ? HAVE_N : HAVE_UPPER_N; /* ν or Ν */
            if (c == 236 || c == 204) return (c == 236) ? HAVE_M : HAVE_UPPER_M; /* μ or Μ */
	    printf("%s", translated);
            return ANY;

            /* If invalid character follows tonos */
            printf("'%s", translated);
            return ANY;

        case HAVE_N:
            if (c == 244 || c == 212) { /* τ or Τ */
                printf("d"); /* ντ or νΤ → d */
		return ANY;
            } else {
                printf("n%s", translated);
            }
            return ANY;

        case HAVE_M:
            if (c == 240 || c == 208) { /* π or Π */
                printf("b"); /* μπ or μΠ → b */
                return ANY;
	    } else {
                printf("m%s", translated);
            }
            return ANY;

	case HAVE_UPPER_N:
            if (c == 244) return HAVE_UPPER_N_LOWER_T; /* Ντ case */
            if (c == 212) { /* Τ */
                printf("D"); /* ΝΤ → D */
		return ANY;
            } else {
                printf("N%s", translated);
            }
            return ANY;

        case HAVE_UPPER_M:
            if (c == 240) return HAVE_UPPER_M_LOWER_P; /* Μπ case */
            if (c == 208) { /* Π */
                printf("B"); /* ΜΠ → B */
		return ANY;
            } else {
                printf("M%s", translated);
            }
            return ANY;

        case HAVE_UPPER_N_LOWER_T:
            printf("D"); /* Ντ → D */
            return ANY;

        case HAVE_UPPER_M_LOWER_P:
            printf("B"); /* Μπ → B */
            return ANY;
    }
    return ANY;
}
int main() {
    int c;
    State S = ANY;

    while ((c = getchar()) != EOF) {
        S = process_character(S, c);
    }
    return 0;
}
