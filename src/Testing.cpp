#include "include/Testing.h"


#ifndef STANDALONE
#include <Rcpp.h>
using namespace Rcpp;
#endif

// This should be the only function besides those in Testing.h that uses cout and cerr.
int testUtility()
{
    int error = 0;
    int globalError = 0;

    error = my_print("Product: %, Qty: %, Price is %", "Shampoo\n", 5, 100);

    if (error)
    {
        std::cerr << "Error in my_print.\n";
        globalError = 1;
    }

    error = my_printError("Product: %, Qty: %, Price is %", "Shampoo\n", 5, 100);

    if (error)
    {
        std::cerr << "Error in my_printError\n";
        globalError = 1;
    }

    return globalError;
}


int testSequenceSummary()
{
    SequenceSummary SS("ATGCTCATTCTCACTGCTGCCTCGTAG");
    int error = 0;
    int globalError = 0;

    //----------------------------//
    //------ Clear Function ------//
    //----------------------------//
    SS.clear();
    for (unsigned i = 0; i < 64; i++)
    {
        if (0 != SS.getCodonCountForCodon(i))
        {
            my_printError("Problem with Sequence Summary \"clear\" function.\n");
            my_printError("Problem at codon index %\n.", i);
            error = 1;
            globalError = 1;
        }
    }
    for (unsigned i = 0; i < 22; i++)
    {
        if (0 != SS.getAACountForAA(i))
        {
            my_printError("Problem with Sequence Summary \"clear\" function.\n");
            my_printError("Problem at amino acid index i\n");
            error = 1;
            globalError = 1;
        }
    }

    if (!error)
        my_print("Sequence Summary clear --- Pass\n");
    else
        error = 0; //Reset for next function.

    //--------------------------------------//
    //------ ProcessSequence Function ------//
    //--------------------------------------//
    SS.processSequence("ATGCTCATTCTCACTGCTGCCTCGTAG");

    if (1 != SS.getAACountForAA("I"))
    {
        my_printError("Problem with Sequence Summary \"processSequence\" function.\n");
        my_printError("Problem with amino acid \"I\".");
        my_printError("I is in the sequence once, but is returning %\n", SS.getAACountForAA("I"));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getAACountForAA("T"))
    {
        my_printError("Problem with Sequence Summary \"processSequence\" function.\n");
        my_printError("Problem with amino acid \"T\".");
        my_printError("T is in the sequence once, but is returning %\n", SS.getAACountForAA("T"));
        error = 1;
        globalError = 1;
    }

    std::string codon = "ATT";
    if (1 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Problem with Sequence Summary \"processSequence\" function.\n");
        my_printError("Problem with codon \"ATT\".");
        my_printError("ATT is in the sequence once, but is returning %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    codon = "ACT";
    if (1 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Problem with Sequence Summary \"processSequence\" function.\n");
        my_printError("Problem with codon \"ACT\".");
        my_printError("ACT is in the sequence once, but is returning %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    codon = "GCT";
    if (1 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Problem with Sequence Summary \"processSequence\" function.\n");
        my_printError("Problem with codon \"GCT\".");
        my_printError("GCT is in the sequence once, but is returning %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    codon = "GCC";
    if (1 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Problem with Sequence Summary \"processSequence\" function.\n");
        my_printError("Problem with codon \"GCC\".");
        my_printError("GCC is in the sequence once, but is returning %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    std::vector <unsigned> *tmp;
    tmp = SS.getCodonPositions("CTC");
    if ((1 != tmp -> at(0)) && (3 != tmp -> at(1)))
    {
        my_printError("Codon CTC should be found at position 1 and 3(zero indexed), but is");
        my_printError("found at these locations:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions("ATT");
    if (2 != tmp -> at(0))
    {
        my_printError("Codon ATT should be found at position 2(zero indexed), but is");
        my_printError("found at these locations:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Sequence Summary processSequence --- Pass\n");
    else
        error = 0; //Reset for next function.

    //------------------------------------------//
    //------ complimentNucleotide Function------//
    //------------------------------------------//

    if ('T' != SequenceSummary::complimentNucleotide('A'))
    {
        my_printError("The compliment of A should be T\n");
        error = 1;
        globalError = 1;
    }

    if ('A' != SequenceSummary::complimentNucleotide('T'))
    {
        my_printError("The compliment of T should be A\n");
        error = 1;
        globalError = 1;
    }

    if ('G' != SequenceSummary::complimentNucleotide('C'))
    {
        my_printError("The compliment of C should be G\n");
        error = 1;
        globalError = 1;
    }

    if ('C' != SequenceSummary::complimentNucleotide('G'))
    {
        my_printError("The compliment of G should be C\n");
        error = 1;
        globalError = 1;
    }

    if ('C' != SequenceSummary::complimentNucleotide('Q'))
    {
        my_printError("The compliment of Q should be C\n");
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Sequence Summary complimentNucleotide --- Pass\n");
    else
        error = 0; //Reset for next function.

    //----------------------------------------------//
    //------ getAACountForAA(string) Function ------//
    //----------------------------------------------//

    if (1 != SS.getAACountForAA("M"))
    {
        my_printError("Error with getAACountForAA(string) for amino acid M.\n");
        my_printError("Should return 1, returns %\n", SS.getAACountForAA("M"));
        error = 1;
        globalError = 1;
    }

    if (2 != SS.getAACountForAA("L"))
    {
        my_printError("Error with getAACountForAA(string) for amino acid L.\n");
        my_printError("Should return 2, returns %\n", SS.getAACountForAA("L"));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getAACountForAA("I"))
    {
        my_printError("Error with getAACountForAA(string) for amino acid I.\n");
        my_printError("Should return 1, returns %\n", SS.getAACountForAA("I"));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getAACountForAA("T"))
    {
        my_printError("Error with getAACountForAA(string) for amino acid T.\n");
        my_printError("Should return 1, returns %\n", SS.getAACountForAA("T"));
        error = 1;
        globalError = 1;
    }

    if (2 != SS.getAACountForAA("A"))
    {
        my_printError("Error with getAACountForAA(string) for amino acid A.\n");
        my_printError("Should return 2, returns %\n", SS.getAACountForAA("A"));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getAACountForAA("S"))
    {
        my_printError("Error with getAACountForAA(string) for amino acid S.\n");
        my_printError("Should return 1, returns %\n", SS.getAACountForAA("S"));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getAACountForAA("X"))
    {
        my_printError("Error with getAACountForAA(string) for amino acid X.\n");
        my_printError("Should return 1, returns %\n", SS.getAACountForAA("X"));
        error = 1;
        globalError = 1;
    }

    if (0 != SS.getAACountForAA("G"))
    {
        my_printError("Error with getAACountForAA(string) for amino acid G.\n");
        my_printError("Should return 0, returns %\n", SS.getAACountForAA("G"));
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Sequence Summary getAACountForAA(string) --- Pass\n");
    else
        error = 0; //Reset for next function.

    //---------------------------------------------//
    //------ getAACountForAA(index) Function ------//
    //---------------------------------------------//
    if (1 != SS.getAACountForAA(10))
    {
        my_printError("Error with getAACountForAA(index) for amino acid M (index 10).\n");
        my_printError("Should return 1, returns %\n", SS.getAACountForAA(10));
        error = 1;
        globalError = 1;
    }

    if (2 != SS.getAACountForAA(9))
    {
        my_printError("Error with getAACountForAA(index) for amino acid L (index 9).\n");
        my_printError("Should return 2, returns %\n", SS.getAACountForAA(9));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getAACountForAA(7))
    {
        my_printError("Error with getAACountForAA(index) for amino acid I (index 7).\n");
        my_printError("Should return 1, returns %\n", SS.getAACountForAA(7));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getAACountForAA(16))
    {
        my_printError("Error with getAACountForAA(index) for amino acid T (index 16).\n");
        my_printError("Should return 1, returns %\n", SS.getAACountForAA(16));
        error = 1;
        globalError = 1;
    }

    if (2 != SS.getAACountForAA(0))
    {
        my_printError("Error with getAACountForAA(index) for amino acid A (index 0).\n");
        my_printError("Should return 2, returns %\n", SS.getAACountForAA(0));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getAACountForAA(15))
    {
        my_printError("Error with getAACountForAA(index) for amino acid S (index 15).\n");
        my_printError("Should return 1, returns %\n", SS.getAACountForAA(15));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getAACountForAA(21))
    {
        my_printError("Error with getAACountForAA(index) for amino acid X (index 21).\n");
        my_printError("Should return 1, returns %\n", SS.getAACountForAA(21));
        error = 1;
        globalError = 1;
    }

    if (0 != SS.getAACountForAA(2))
    {
        my_printError("Error with getAACountForAA(index) for amino acid D (index 2).\n");
        my_printError("Should return 0, returns %\n", SS.getAACountForAA(2));
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Sequence Summary getAACountForAA(index) --- Pass\n");
    else
        error = 0; //Reset for next function.

    //--------------------------------------------//
    //------ getCodonCountsForCodon(string) ------//
    //--------------------------------------------//

    codon = "ATG";
    if (1 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Error with getCodonCountForCodon(string) for %.\n", codon);
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    codon = "CTC";
    if (2 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Error with getCodonCountForCodon(string) for %.\n", codon);
        my_printError("Should return 2, but returns %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    codon = "ATT";
    if (1 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Error with getCodonCountForCodon(string) for %.\n", codon);
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    codon = "ACT";
    if (1 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Error with getCodonCountForCodon(string) for %.\n", codon);
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    codon = "GCT";
    if (1 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Error with getCodonCountForCodon(string) for %.\n", codon);
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    codon = "GCC";
    if (1 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Error with getCodonCountForCodon(string) for %.\n", codon);
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    codon = "TCG";
    if (1 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Error with getCodonCountForCodon(string) for %.\n", codon);
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    codon = "TAG";
    if (1 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Error with getCodonCountForCodon(string) for %.\n", codon);
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    codon = "AAA";
    if (0 != SS.getCodonCountForCodon(codon))
    {
        my_printError("Error with getCodonCountForCodon(string) for %.\n", codon);
        my_printError("Should return 0, but returns %\n", SS.getCodonCountForCodon(codon));
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Sequence Summary getCodonCountsForCodon(string) --- Pass\n");
    else
        error = 0; //Reset for next function.

    //----------------------------------------------------//
    //------ getCodonCountsForCodon(index) Function ------//
    //----------------------------------------------------//

    if (1 != SS.getCodonCountForCodon(29))
    {
        my_printError("Error with getCodonCountForCodon(index) for codon \"ATG\" (index 29).\n");
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(29));
        error = 1;
        globalError = 1;
    }

    if (2 != SS.getCodonCountForCodon(24))
    {
        my_printError("Error with getCodonCountForCodon(index) for codon \"CTC\" (index 24).\n");
        my_printError("Should return 2, but returns %\n", SS.getCodonCountForCodon(24));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getCodonCountForCodon(20))
    {
        my_printError("Error with getCodonCountForCodon(index) for codon \"ATT\" (index 20).\n");
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(20));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getCodonCountForCodon(51))
    {
        my_printError("Error with getCodonCountForCodon(index) for codon \"ACT\" (index 51).\n");
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(51));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getCodonCountForCodon(3))
    {
        my_printError("Error with getCodonCountForCodon(index) for codon \"GCT\" (index 3).\n");
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(3));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getCodonCountForCodon(1))
    {
        my_printError("Error with getCodonCountForCodon(index) for codon \"GCC\" (index 1).\n");
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(1));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getCodonCountForCodon(46))
    {
        my_printError("Error with getCodonCountForCodon(index) for codon \"TCG\" (index 46).\n");
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(46));
        error = 1;
        globalError = 1;
    }

    if (1 != SS.getCodonCountForCodon(62))
    {
        my_printError("Error with getCodonCountForCodon(index) for codon \"TAG\" (index 62).\n");
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(62));
        error = 1;
        globalError = 1;
    }

    if (0 != SS.getCodonCountForCodon(2))
    {
        my_printError("Error with getCodonCountForCodon(index) for codon \"AAA\" (index 2).\n");
        my_printError("Should return 1, but returns %\n", SS.getCodonCountForCodon(2));
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Sequence Summary getCodonCountsForCodon(index) --- Pass\n");
    else
        error = 0; //Reset for next function.

    //---------------------------------------------------------------//
    //------ getRFPObserved(string) & setRFPObserved Functions ------//
    //---------------------------------------------------------------//

    SS.setRFPObserved(4, 35);
    SS.setRFPObserved(16,45);
    SS.setRFPObserved(54,2);
    SS.setRFPObserved(45,0);

    if (35 != SS.getRFPObserved("TGC"))
    {
        my_printError("Error in getRFPObserved(string) or setRFPObserved for codon \"TGC\".\n");
        my_printError("should return 35, but returns %\n", SS.getRFPObserved("TGC"));
        error = 1;
        globalError = 1;
    }

    if (45 != SS.getRFPObserved("CAC"))
    {
        my_printError("Error in getRFPObserved(string) or setRFPObserved for codon \"CAC\".\n");
        my_printError("should return 45, but returns %\n", SS.getRFPObserved("CAC"));
        error = 1;
        globalError = 1;
    }

    if (2 != SS.getRFPObserved("GTG"))
    {
        my_printError("Error in getRFPObserved(string) or set RFPObserved for codon \"GTG\".\n");
        my_printError("should return 2, but returns %\n", SS.getRFPObserved("GTG"));
        error = 1;
        globalError = 1;
    }

    if (0 != SS.getRFPObserved("TCC"))
    {
        my_printError("Error in getRFPObserved(string) or setRFPObserved for codon \"TCC\".\n");
        my_printError("should return 0, but returns %\n", SS.getRFPObserved("TCC"));
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Sequence Summary getRFPObserved(string) & setRFPObserved --- Pass\n");
    else
        error = 0; //Reset for next function.

    //--------------------------------------------//
    //------ getRFPObserved(index) Function ------//
    //--------------------------------------------//

    SS.setRFPObserved(0,45);
    SS.setRFPObserved(1,52);
    SS.setRFPObserved(2,63);
    SS.setRFPObserved(60,23);

    if (45 != SS.getRFPObserved(0))
    {
        my_printError("Error with getRFPObserved(index) for codon index 0.\n");
        my_printError("should return 45, but returns %\n", SS.getRFPObserved(0));
        error = 1;
        globalError = 1;
    }

    if (52 != SS.getRFPObserved(1))
    {
        my_printError("Error with getRFPObserved(index) for codon index 1.\n");
        my_printError("should return 52, but returns %\n", SS.getRFPObserved(1));
        error = 1;
        globalError = 1;
    }

    if (63 != SS.getRFPObserved(2))
    {
        my_printError("Error with getRFPObserved(index) for codon index 2.\n");
        my_printError("should return 63, but returns %\n", SS.getRFPObserved(2));
        error = 1;
        globalError = 1;
    }

    if (23 != SS.getRFPObserved(60))
    {
        my_printError("Error with getRFPObserved(index) for codon index 60.\n");
        my_printError("should return 23, but returns %\n", SS.getRFPObserved(60));
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Sequence Summary getRFPObserved(index) --- Pass\n");
    else
        error = 0; //Reset for next function.

    //------------------------------------------------//
    //------ getCodonPositions(string) Function ------//
    //------------------------------------------------//

    tmp = SS.getCodonPositions("ATG");
    if (tmp -> at(0) != 0 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(string) for codon \"ATG\".\n");
        my_printError("Should return 0, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions("CTC");
    if (tmp -> at(0) != 1 || tmp -> at(1) != 3|| tmp -> size() != 2)
    {
        my_printError("Error with getCodonPositions(string) for codon \"CTC\".\n");
        my_printError("Should return 1 and 3, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions("ATT");
    if (tmp -> at(0) != 2 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(string) for codon \"ATT\".\n");
        my_printError("Should return 2, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions("ACT");
    if (tmp -> at(0) != 4 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(string) for codon \"ACT\".\n");
        my_printError("Should return 4, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }


    tmp = SS.getCodonPositions("GCT");
    if (tmp -> at(0) != 5 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(string) for codon \"GCT\".\n");
        my_printError("Should return 5, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions("GCC");
    if (tmp -> at(0) != 6 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(string) for codon \"GCC\".\n");
        my_printError("Should return 6, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions("TCG");
    if (tmp -> at(0) != 7 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(string) for codon \"TCG\".\n");
        my_printError("Should return 7, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions("TAG");
    if (tmp -> at(0) != 8 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(string) for codon \"TAG\".\n");
        my_printError("Should return 8, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions("GTG");
    if (tmp -> size() != 0)
    {
        my_printError("Error with getCodonPositions(string) for codon \"GTG\".\n");
        my_printError("Should return an empty vector, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Sequence Summary getCodonPositions(string) --- Pass\n");
    else
        error = 0; //Reset for next function.

    //-----------------------------------------------//
    //------ getCodonPositions(index) Function ------//
    //-----------------------------------------------//

    tmp = SS.getCodonPositions(29);
    if (tmp -> at(0) != 0 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(index) for codon index 29.\n");
        my_printError("Should return 0, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions(24);
    if (tmp -> at(0) != 1 || tmp -> at(1) != 3 || tmp -> size() != 2)
    {
        my_printError("Error with getCodonPositions(index) for codon index 24.\n");
        my_printError("Should return 1 and 3, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions(20);
    if (tmp -> at(0) != 2 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(index) for codon index 20.\n");
        my_printError("Should return 2, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions(51);
    if (tmp -> at(0) != 4 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(index) for codon index 51.\n");
        my_printError("Should return 4, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions(3);
    if (tmp -> at(0) != 5 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(index) for codon index 3.\n");
        my_printError("Should return 4, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions(1);
    if (tmp -> at(0) != 6 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(index) for codon index 1.\n");
        my_printError("Should return 4, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions(46);
    if (tmp -> at(0) != 7 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(index) for codon index 46.\n");
        my_printError("Should return 7, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions(62);
    if (tmp -> at(0) != 8 || tmp -> size() != 1)
    {
        my_printError("Error with getCodonPositions(index) for codon index 62.\n");
        my_printError("Should return 8, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    tmp = SS.getCodonPositions(54);
    if (tmp -> size() != 0)
    {
        my_printError("Error with getCodonPositions(index) for codon index 54.\n");
        my_printError("Should return an empty vector, but returns:\n");
        for (unsigned i = 0; i < tmp -> size(); i++)
        {
            my_printError("%\n", tmp -> at(i));
        }
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Sequence Summary getCodonPositions(index) --- Pass\n");
    else
        error = 0; //Reset for next function.

    //----------------------------------------//
    //------ get/setRFP_count Functions ------//
    //----------------------------------------//
    std::vector <unsigned> tmp2 = SS.getRFP_count();

    if (0 != tmp2.size())
    {
        my_printError("Error with getRFP_count. Function should return an empty vector but returns:\n");
        for (unsigned i = 0; i < tmp2.size(); i++)
        {
            my_printError("%\n", tmp2[i]);
        }
        error = 1;
        globalError = 1;
    }

    tmp2 = {1, 2, 3, 4, 5};
    SS.setRFP_count(tmp2);

    if (SS.getRFP_count() != tmp2)
    {
        my_printError("Error in getRFP_count or setRFP_count. Function should return 1, 2, 3, 4, 5, but returns:\n");
        for (unsigned i = 0; i < tmp2.size(); i++)
        {
            my_printError("%\n", tmp2[i]);
        }
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Sequence Summary get/setRFP_count --- Pass\n");

    // No need to reset error

    return globalError;
}


int testGene()
{
    Gene testGene;
    int error = 0;
    int globalError = 0;

    //---------------------------------//
    //------ get/setId Functions ------//
    //---------------------------------//
    testGene.setId("testGene");

    if (testGene.getId() != "testGene") {
        my_printError("Error in setId or getId.\n");
        globalError = 1;
    }
    else
        my_print("Gene get/setId --- Pass\n");

    //------------------------------------------//
    //------ get/setDescription Functions ------//
    //------------------------------------------//
    testGene.setDescription("Test Gene for Unit Testing");

    if (testGene.getDescription() != "Test Gene for Unit Testing")
    {
        my_printError("Error in setDescription or getDescription.\n");
        globalError = 1;
    }
    else
        my_print("Gene get/setDescription --- Pass\n");

    //---------------------------------------//
    //------ get/setSequence Functions ------//
    //---------------------------------------//
    testGene.setSequence("ATGCTCATTCTCACTGCTGCCTCGTAG");

    if (testGene.getSequence() != "ATGCTCATTCTCACTGCTGCCTCGTAG")
    {
        my_printError("Error in setSequence or getSequence.\n");
        globalError = 1;
    }
    else
        my_print("Gene get/setSequence --- Pass\n");

    //----------------------------------------//
    //------ get/addRFP_count Functions ------//
    //----------------------------------------//
    std::vector <unsigned> rfp_counts = {0, 1, 1};

    testGene.addRFP_count(rfp_counts);
    if (testGene.getRFP_count() != rfp_counts)
    {
        my_printError("Error in getRFP_count or addRFP_count.\n");
        globalError = 1;
    }
    else
        my_print("Gene get/addRFP_count --- Pass\n");

    //-----------------------------------------//
    //------ getSequenceSummary Function ------//
    //-----------------------------------------//
    SequenceSummary SS("ATGCTCATTCTCACTGCTGCCTCGTAG");
    SequenceSummary *GeneSS = testGene.getSequenceSummary();
    for (unsigned i = 0; i < 64; i++)
    {
        if (SS.getCodonCountForCodon(i) != GeneSS->getCodonCountForCodon(i))
        {
            my_printError("Error with getSequenceSummary. Codon counts are incorrect");
            my_printError(" for codon %, %.\n", i, SequenceSummary::codonArray[i]);
            my_printError("Should return %, but returns %\n", SS.getCodonCountForCodon(i), GeneSS->getCodonCountForCodon(i));
            error = 1;
            globalError = 1;
        }
    }

    for (unsigned i = 0; i < 64; i++)
    {
        if (SS.getRFPObserved(i) != GeneSS->getRFPObserved(i))
        {
            my_printError("Error with getSequenceSummary. RFP observed is incorrect");
            my_printError(" for codon %.\n", i);
            my_printError("Should return %, but reutrns %\n", SS.getRFPObserved(i), GeneSS->getRFPObserved(i));
            error = 1;
            globalError = 1;
        }
    }

    //This fails because this returns pointers to vectors and they need to be compared differently.
    std::vector <unsigned> *SSvec;
    std::vector <unsigned> *Gvec;
    for (unsigned i = 0; i < 64; i++)
    {
        SSvec = SS.getCodonPositions(i);
        Gvec = GeneSS->getCodonPositions(i);
        if (SSvec->size() != Gvec->size())
        {
            my_printError("Error with getSequenceSummary. Codon positions are incorrect.\n");
            my_printError("Information in compared vectors are not of equal size.\n");
            error = 1;
            globalError = 1;
        }
        else
        {
            for (unsigned j = 0; j < SSvec->size(); j++)
            {
                if (SSvec->at(j) != Gvec->at(j))
                {
                    my_printError("Error with getSequenceSummary. Codon positions are incorrect");
                    my_printError(" for codon %.\n", i);
                    my_printError("Should return %, but returns %\n", SSvec->at(j), Gvec->at(j));
                    error = 1;
                    globalError = 1;
                }
            }
        }
    }

    unsigned AAListSize = (unsigned)SequenceSummary::aminoAcids().size();
    for (unsigned i = 0; i < AAListSize; i++)
    {
        if (SS.getAACountForAA(i) != GeneSS->getAACountForAA(i))
        {
            my_printError("Error with getSequenceSummary. AA counts are incorrect");
            my_printError(" for amino acid %.\n", i);
            my_printError("Should return %, but returns %\n", SS.getAACountForAA(i), GeneSS->getAACountForAA(i));
            error = 1;
            globalError = 1;
        }
    }
    if (!error)
        my_print("Gene getSequenceSummary --- Pass\n");
    else
        error = 0; //Reset for next function.

    //----------------------------------------------------------//
    //------ get/setObservedSynthesisRateValues Functions ------//
    //----------------------------------------------------------//
    std::vector <double> tmp;
    tmp = testGene.getObservedSynthesisRateValues();

    if (0 != tmp.size())
    {
        my_printError("Error with getObservedSynthesisRateValues. Function should return an empty vector but returns:\n");
        for (unsigned i = 0; i < tmp.size(); i++)
        {
            my_printError("%\n", tmp[i]);
        }
        error = 1;
        globalError = 1;
    }

    tmp = {2.34, 3.234, 0.123};
    testGene.setObservedSynthesisRateValues(tmp);

    if (testGene.getObservedSynthesisRateValues() != tmp)
    {
        my_printError("Error in getObservedSynthesisRateValues or setObservedSynthesisRateValues. Function should return 2.34, 3.234, 0.123, but returns:\n");
        for (unsigned i = 0; i < tmp.size(); i++)
        {
            my_printError("%\n", tmp[i]);
        }
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Gene get/setObservedSynthesisRateValues --- Pass\n");
    else
        error = 0; //Reset for next function.

    //--------------------------------------------------//
    //------ getNumObservedSynthesisSets Function ------//
    //--------------------------------------------------//
    if (3 != testGene.getNumObservedSynthesisSets())
    {
        my_printError("Error with getNumObservedSynthesisSets. Function should return 3, but returns ");
        my_printError("%.\n", testGene.getNumObservedSynthesisSets());
        globalError = 1;
    }
    else
        my_print("Gene getNumObservedSynthesisSets --- Pass\n");

    //-----------------------------------------------//
    //------ getObservedSynthesisRate Function ------//
    //-----------------------------------------------//

    // Declared above: tmp = {2.34, 3.234, 0.123}

    for (unsigned i = 0; i < 3; i++)
    {
        if (testGene.getObservedSynthesisRate(i) != tmp[i])
        {
            my_printError("Error with getObservedSynthesisRate. Function should return % at index", tmp[i]);
            my_printError("%, but returns %.\n", i, testGene.getObservedSynthesisRate(i));
            error = 1;
            globalError = 1;
        }
    }

    if (!error)
        my_print("Gene getObservedSynthesisRate --- Pass\n");
    else
        error = 0; //Reset for next function.

    //--------------------------------------//
    //------ getNucleotideAt Function ------//
    //--------------------------------------//
    if ('A' != testGene.getNucleotideAt(0))
    {
        my_printError("Error with getNucleotideAt. At index 0, the return value should be 'A', but is ");
        my_printError("%\n", testGene.getNucleotideAt(0));
        error = 1;
        globalError = 1;
    }
    if ('T' != testGene.getNucleotideAt(1))
    {
        my_printError("Error with getNucleotideAt. At index 1, the return value should be 'T', but is ");
        my_printError("%\n", testGene.getNucleotideAt(1));
        error = 1;
        globalError = 1;
    }
    if ('G' != testGene.getNucleotideAt(2))
    {
        my_printError("Error with getNucleotideAt. At index 2, the return value should be 'G', but is ");
        my_printError("%\n", testGene.getNucleotideAt(2));
        error = 1;
        globalError = 1;
    }
    if ('C' != testGene.getNucleotideAt(3))
    {
        my_printError("Error with getNucleotideAt. At index 3, the return value should be 'C', but is ");
        my_printError("%\n", testGene.getNucleotideAt(3));
        error = 1;
        globalError = 1;
    }
    if ('T' != testGene.getNucleotideAt(10))
    {
        my_printError("Error with getNucleotideAt. At index 10, the return value should be 'T', but is ");
        my_printError("%\n", testGene.getNucleotideAt(10));
        error = 1;
        globalError = 1;
    }
    if ('G' != testGene.getNucleotideAt(23))
    {
        my_printError("Error with getNucleotideAt. At index 23, the return value should be 'G', but is ");
        my_printError("%\n", testGene.getNucleotideAt(23));
        error = 1;
        globalError = 1;
    }
    if ('G' != testGene.getNucleotideAt(26))
    {
        my_printError("Error with getNucleotideAt. At index 26, the return value should be 'G', but is ");
        my_printError("%\n", testGene.getNucleotideAt(26));
        error = 1;
        globalError = 1;
    }
    if (!error)
        my_print("Gene getNucleotideAt --- Pass\n");
    else
        error = 0; //Reset for next function.

    //Todo: consider out of range test case?

    //-----------------------------//
    //------ length Function ------//
    //-----------------------------//
    if (testGene.length() == strlen("ATGCTCATTCTCACTGCTGCCTCGTAG"))
        my_print("Gene length --- Pass\n");
    else
    {
        my_printError("Error with length. Should return ");
        my_printError("% but returns: %\n", strlen("ATGCTCATTCTCACTGCTGCCTCGTAG"), testGene.length());
        globalError = 1;
    }

    //----------------------------------------//
    //------ reverseComplement Function ------//
    //----------------------------------------//
    Gene tmpGene;
    tmpGene = testGene.reverseComplement();
    if ("CTACGAGGCAGCAGTGAGAATGAGCAT" == tmpGene.getSequence())
        my_print("Gene reverseComplement --- Pass\n");
    else
    {
        my_printError("Error with reverseComplement. Should return \"CTACGAGGCAGCAGTGAGAATGAGCAT\" but returns: ");
        my_printError("%\n", tmpGene.getSequence());
        globalError = 1;
    }

    //-----------------------------------//
    //------ toAASequence Function ------//
    //-----------------------------------//
    if ("MLILTAASX" == testGene.toAASequence())
        my_print("Gene toAASequence --- Pass\n");
    else
    {
        my_printError("Error with toAASequence. Should return \"MLILTAASX\", but returns: %\n", testGene.toAASequence());
        globalError = 1;
    }

    //----------------------------//
    //------ clear Function ------//
    //----------------------------//
    testGene.clear();
    if ("" != testGene.getId())
    {
        my_printError("Error with clear. Gene Id should be blank, but is %.\n", testGene.getId());
        error = 1;
        globalError = 1;
    }
    if ("" != testGene.getDescription())
    {
        my_printError("Error with clear. Gene description should be blank, but is %.\n", testGene.getDescription());
        error = 1;
        globalError = 1;
    }
    if ("" != testGene.getSequence())
    {
        my_printError("Error with clear. Gene sequence should be blank, but is %.\n", testGene.getSequence());
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Gene clear --- Pass\n");
    // No need to reset error

    return globalError;
}


int testGenome(std::string testFileDir)
{
    Genome genome;
    Genome testGenome;
    Gene g1("ATGGCCACTATTGGGTCTTAG", "TEST001", "TEST001 Test Gene");
    Gene g2("TGGGATTACCAA", "TEST002", "TEST002 Test Gene");
    Gene g3("TTGGAAACCACA", "TEST003", "TEST003 Test Gene");
    Gene g4("TGGGATTACCCC", "TEST004", "TEST004 Test Gene");
    Gene s1("TGGGATTACCAA", "TEST011", "TEST011 Test Gene"); //simulated gene
    int error = 0;
    int globalError = 0;

    /* Section 1:
     * Testing / Gene / Other Functions:
     * addGene, getGene, getGenes,
     * setNumGenesWithPhi, getNumGenesWithPhi, getNumGenesWithPhiForIndex,
     * getGenomeSize, getCodonCountsPerGene, clear
    */

    //TODO: should improper input be given (bad id/index)?

    //-----------------------------------//
    //------ get/addGene Functions ------//
    //-----------------------------------//
    genome.addGene(g1, false);
    genome.addGene(s1, true); //add the simulated gene s1

    Gene test = genome.getGene("TEST001", false);
    Gene test2 = genome.getGene(0, false);
    Gene test3 = genome.getGene("TEST011", true);
    Gene test4 = genome.getGene(0, true);

    if (!(test == g1 && test2 == g1)) //checking both by string and index
    {
        my_printError("Error in addGene or getGene with genes.\n");
        error = 1;
        globalError = 1;
    }

    if (!(test3 == s1 && test4 == s1)) //checking both by string and index
    {
        my_printError("Error in addGene or getGene with simulated genes.\n");
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Genome get/addGene --- Pass\n");
    else
        error = 0; //Reset for next function.

    //-------------------------------//
    //------ getGenes Function ------//
    //-------------------------------//
    std::vector<Gene> testVec;
    testVec.push_back(g1);

    if (!(testVec == genome.getGenes(false))) {
        my_printError("Error in getGenes(false).\n");
        error = 1;
        globalError = 1;
    }

    testVec.clear();
    testVec.push_back(s1);

    if (!(testVec == genome.getGenes(true))) {
        my_printError("Error in getGenes(true).\n");
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Genome getGenes --- Pass\n");
    else
        error = 0; //Reset for next function.

    //----------------------------------------------//
    //------ get/setNumGenesWithPhi Functions ------//
    //----------------------------------------------//
    genome.setNumGenesWithPhi({0, 1, 2, 3});

    std::vector<unsigned> uVector = {0, 1, 2, 3};

    if (genome.getNumGenesWithPhi() == uVector)
        my_print("Genome get/setNumGenesWithPhi --- Pass\n");
    else
    {
        my_printError("Error in setNumGenesWithPhi or getNumGenesWithPhi.\n");
        globalError = 1;
    }

    //-------------------------------------------------//
    //------ getNumGenesWithPhiForIndex Function ------//
    //-------------------------------------------------//
    for (unsigned i = 1; i < 4; i++) {
        if (genome.getNumGenesWithPhiForIndex(i) != i) {
            my_printError("Error in getNumGenesWithPhiForIndex with index %.", i);
            my_printError("Should return %, but returns %.\n", i, genome.getNumGenesWithPhiForIndex(i));
            error = 1;
            globalError = 1;
        }
    }

    if (!error)
        my_print("Genome getNumGenesWithPhiForIndex --- Pass\n");
    else
        error = 0; //Reset for next function.

    //------------------------------------//
    //------ getGenomeSize Function ------//
    //------------------------------------//
    if (1 != genome.getGenomeSize(false)) {
        my_printError("Error in getGenomesize(false). Should return 1, but returns %.\n", genome.getGenomeSize(false));
        error = 1;
        globalError = 1;
    }

    if (1 != genome.getGenomeSize(true)) {
        my_printError("Error in getGenomesize(true). Should return 1, but returns %.\n", genome.getGenomeSize(true));
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Genome getGenomeSize --- Pass\n");
    else
        error = 0; //Reset for next function.

    //--------------------------------------------//
    //------ getCodonCountsPerGene Function ------//
    //--------------------------------------------//

    //reuse generic vector of unsigned integers
    uVector = {1};
    if (uVector != genome.getCodonCountsPerGene("ATG")) {
        my_printError("Error in getCodonCountsPerGene with a single gene.\n");
        error = 1;
        globalError = 1;
    }

    genome.addGene(g2);
    genome.addGene(g4);

    uVector = {0, 1, 1};

    if (uVector != genome.getCodonCountsPerGene("GAT")) {
        my_printError("Error in getCodonCountsPerGene with three genes.\n");
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Genome getCodonCountsPerGene --- Pass\n");
    else
        error = 0; //Reset for next function.

    //----------------------------//
    //------ Clear Function ------//
    //----------------------------//

    // Empty Genome as a control variable
    Genome empty;

    // Test adding ObservedSynthesisRateValues
    Gene clear1("TTGATCGGGCAT", "TEST005", "TEST005 Test Gene");
    clear1.setObservedSynthesisRateValues({1, 2, 3, 4});
    genome.addGene(clear1, false);

    genome.clear();

    if (genome == empty)
        my_print("Genome clear --- Pass\n");
    else
    {
        my_printError("Error in clear. Genome is not empty.\n");
        globalError = 1;
    }

    /* Section 2:
     * Other and File I/O Functions:
     * getGenomeForGeneIndices
     * readFasta
     * readPANSEFile
     * readObservedPhiValues
    */

    //-----------------------------------------------//
    //------ getGenomeForGeneIndices Function ------//
    //-----------------------------------------------//

    // add more simulated and non-simulated genes
    genome.addGene(g1, false);
    genome.addGene(g2, false);
    genome.addGene(g3, false);
    genome.addGene(g4, false);

    //reuse generic vector of unsigned integers
    uVector = {0, 1, 2, 3};

    if (!(genome == genome.getGenomeForGeneIndices(uVector, false))) {
        my_printError("Error in getGenomeForGeneIndices with genes.\n");
        error = 1;
        globalError = 1;
    }

    genome.clear();

    Gene s2("TAGCATGATCCA", "TEST012", "TEST002 Test Gene"); //simulated gene
    Gene s3("TCATCAGGATTC", "TEST013", "TEST002 Test Gene"); //simulated gene
    Gene s4("AAACATGTCACG", "TEST014", "TEST002 Test Gene"); //simulated gene

    genome.addGene(s1, true);
    genome.addGene(s2, true);
    genome.addGene(s3, true);
    genome.addGene(s4, true);

    if (!(genome == genome.getGenomeForGeneIndices(uVector, true))) {
        my_printError("Error in getGenomeForGeneIndices with simulated genes.\n");
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Genome getGenomeForGeneIndices --- Pass\n");
    else
        error = 0; //Reset for next function.

    //--------------------------------//
    //------ readFasta Function ------//
    //--------------------------------//
    genome.clear();
    std::string file = testFileDir + "/" + "test.fasta";
    genome.readFasta(file, false);

    Gene fasta1("ATGACCGTAATTTTTTACTAG", "TEST002", "TEST002 Test Gene");
    Gene fasta2("ATGGTCTACTTTCTGACATAG", "TEST003", "TEST003 Test Gene");

    testGenome.addGene(g1, false);
    testGenome.addGene(fasta1, false);
    testGenome.addGene(fasta2, false);

    if (genome == testGenome)
        my_print("Genome readFasta --- Pass\n");
    else
    {
        my_printError("Error in readFasta. Genomes are not equivalent.\n");
        globalError = 1;
    }

    //---------------------------------//
    //------ writeFasta Function ------//
    //---------------------------------//

    // Now write a genome described above in readFasta to a file, read it in
    // again, and then compare its validity again.
    testGenome.clear();

    file = testFileDir + "/" + "testWrite.fasta";
    genome.writeFasta(file, false);
    testGenome.readFasta(file, false);

    if (!(genome == testGenome))
    {
        my_printError("Error in writeFasta with genes. Genomes are not equivalent.\n");
        error = 1;
        globalError = 1;
    }

    // Now, re-do writing check but with simulated genes.
    testGenome.clear();
    genome.clear();

    genome.addGene(g1, true);
    genome.addGene(fasta1, true);
    genome.addGene(fasta2, true);

    genome.writeFasta(file, true);

    // Note that while these genes were originally simulated, they are printed
    // as non-simulated genes.
    // It is up to the user to know that they were simulated, but they will
    // now be read in as non-simulated genes (and Unit Testing will compare their validity as such)

    testGenome.readFasta(file, true);

    genome.clear();
    genome.addGene(g1, false);
    genome.addGene(fasta1, false);
    genome.addGene(fasta2, false);

    if (!(genome == testGenome))
    {
        my_printError("Error in writeFasta with simulated genes. Genomes are not equivalent.\n");
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Genome writeFasta --- Pass\n");
    else
        error = 0; //Reset for next function. 

    //----------------------------------//
    //------ readRFPFile Function ------//
    //----------------------------------//
    genome.clear();
    testGenome.clear();

    file = testFileDir + "/" + "testReadRFP.csv";
    genome.readRFPFile(file);

    // These sequences are composed of those codons with RFPObserved values > 0
    // Each repetition of a codon denotes an incrementation in RFPObserved for that codon

    Gene rfp1("GCCGCCGCCGCCGCC", "TEST001", "No description for RFP Model");
    Gene rfp2("GCGGCGTTTTTTTTTTTT", "TEST002", "No description for RFP Model");
    Gene rfp3("ATGATGATGATGATGATGATGATGATGATGATGATGATG", "TEST003", "No description for RFP Model");

    testGenome.addGene(rfp1, false);
    testGenome.addGene(rfp2, false);
    testGenome.addGene(rfp3, false);

    if (genome == testGenome)
        my_print("Genome readRFPFile --- Pass\n");
    else
    {
        my_printError("Error in readRFPFile. Genomes are not equivalent.\n");
        globalError = 1;
    }

    //-----------------------------------//
    //------ writeRFPFile Function ------//
    //-----------------------------------//

    /* Now write a genome described above in readRFPFile to a file, read it in
    // again, and then compare its validity again. */
    testGenome.clear();

    file = testFileDir + "/" + "testWriteRFP.csv";
    genome.writeRFPFile(file, false);
    testGenome.readRFPFile(file);

    if (!(genome == testGenome))
    {
        my_printError("Error in writeRFPFile with genes. Genomes are not equivalent.\n");
        error = 1;
        globalError = 1;
    }

    // Now re-do writing check but with simulated genes.
    testGenome.clear();
    genome.clear();

    genome.addGene(rfp1, true);
    genome.addGene(rfp2, true);
    genome.addGene(rfp3, true);

    genome.writeRFPFile(file, true);

    /* Note that while these genes were originally simulated, they are printed
    // as non-simulated genes.
    // It is up to the user to know that they were simulated, but they will
    // now be read in as non-simulated genes (and Unit Testing will compare their validity as such) */

    genome.clear();
    genome.addGene(rfp1, false);
    genome.addGene(rfp2, false);
    genome.addGene(rfp3, false);

    testGenome.readRFPFile(file);

    if (!(genome == testGenome))
    {
        my_printError("Error in writeRFPFile with simulated genes. Genomes are not equivalent.\n");
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("Genome writeRFPFile --- Pass\n");
    else
        error = 0; //Reset for next function.

    //------------------------------------//
    //------ readPANSEFile Function ------//
    //------------------------------------//
    genome.clear();
    testGenome.clear();

    file = testFileDir + "/" + "readPANSE.csv";
    genome.readPANSEFile(file);

    Gene panse1("CTTGCTATTTTT", "TEST001", "No description for PANSE Model");
    Gene panse2("CCTGTAATTTGG", "TEST002", "No description for PANSE Model");

    std::vector <unsigned> tmp1 = {0, 2, 0, 0};
    std::vector <unsigned> tmp2 = {0, 0, 1, 1};

    panse1.addRFP_count(tmp1);
    panse2.addRFP_count(tmp2);

    testGenome.addGene(panse1, false);
    testGenome.addGene(panse2, false);

    if (genome == testGenome)
        my_print("Genome readPANSE --- Pass\n");
    else
    {
        my_printError("Error in readPANSE. Genomes are not equivalent.\n");
        globalError = 1;
    }

    //-------------------------------------//
    //------ writePANSEFile Function ------//
    //-------------------------------------//

    /* readObservedPhiValues Testing Function
     *
     * Compares a genome with the readObservedPhiValues function's created genome.
     * Reads in "readObservedPhiValues.csv" and "readObservedPhiValuesError.csv" twice each,
     * once for byID and once for byIndex.
     *
     * Significant standard error output is produced by design: both files exhibit some errors.
    */
    //--------------------------------------------//
    //------ readObservedPhiValues Function ------//
    //--------------------------------------------//
    genome.clear();
    testGenome.clear();
    std::vector <double> emptyVec; // Empty vector used to clear ObservedSynthesisRateValues

    // Test 1: Test non-error file vs by ID readObservedPhiValues function
    genome.addGene(g1, false);
    g1.setObservedSynthesisRateValues({1, 2, 3, 4});
    testGenome.addGene(g1, false);

    genome.addGene(g2, false);
    g2.setObservedSynthesisRateValues({4, 3, 2, 1});
    testGenome.addGene(g2, false);

    genome.addGene(g3, false);
    g3.setObservedSynthesisRateValues({-1, -1, 4, 2});
    testGenome.addGene(g3, false);

    genome.addGene(g4, false);
    g4.setObservedSynthesisRateValues({2, 1, 4, -1});
    testGenome.addGene(g4, false);

    testGenome.setNumGenesWithPhi({3, 3, 4, 3});

    file = testFileDir + "/" + "readObservedPhiValues.csv";
    genome.readObservedPhiValues(file, true);

    if (!(genome == testGenome))
    {
        my_printError("Error comparing genomes: readObservedPhiValues.csv ");
        my_printError("by ID produces a different genome than expected.\n");
        error = 1;
        globalError = 1;
    }
    genome.clear();

    // Test 2: Test non-error file vs by index readObservedPhiValues function
    // Re-input genome as it was in the previous test, then run it by index instead
    g1.setObservedSynthesisRateValues(emptyVec);
    genome.addGene(g1, false);
    g2.setObservedSynthesisRateValues(emptyVec);
    genome.addGene(g2, false);
    g3.setObservedSynthesisRateValues(emptyVec);
    genome.addGene(g3, false);
    g4.setObservedSynthesisRateValues(emptyVec);
    genome.addGene(g4, false);

    genome.readObservedPhiValues(file, false);

    if (!(genome == testGenome))
    {
        my_printError("Error comparing genomes: readObservedPhiValues.csv ");
        my_printError("by index produces a different genome than expected.\n");
        error = 1;
        globalError = 1;
    }
    genome.clear();
    testGenome.clear();

    // Test 3: Test error file vs by ID readObservedPhiValues function
    // Since this file has an error in number of phi values, the ObservedSynthesisRateValues are cleared
    genome.addGene(g1, false);
    testGenome.addGene(g1, false);

    genome.addGene(g2, false);
    testGenome.addGene(g2, false);

    genome.addGene(g3, false);
    testGenome.addGene(g3, false);

    genome.addGene(g4, false);
    testGenome.addGene(g4, false);

    // As discussed in the documentation, however, NumGenesWithPhi is still initialized with 0's despite the error
    testGenome.setNumGenesWithPhi({0, 0, 0, 0});

    file = testFileDir + "/" + "readObservedPhiValuesError.csv";
    genome.readObservedPhiValues(file, true);

    if (!(genome == testGenome))
    {
        my_printError("Error comparing genomes: readObservedPhiValuesError.csv ");
        my_printError("by ID produces a different genome than expected.\n");
        error = 1;
        globalError = 1;
    }

    genome.clear();

    // Test 4: Test error file vs by index readObservedPhiValues function
    // Re-input genome as it was in the previous test, then run it by index instead
    genome.addGene(g1, false);
    genome.addGene(g2, false);
    genome.addGene(g3, false);
    genome.addGene(g4, false);

    genome.readObservedPhiValues(file, false);

    if (!(genome == testGenome))
    {
        my_printError("Error comparing genomes: readObservedPhiValuesError.csv ");
        my_printError("by index produces a different genome than expected.\n");
        error = 1;
        globalError = 1;
    }

    // If any errors are produced, reset variable for next function
    if (!error)
        my_print("Genome readObservedPhiValues --- Pass\n");
    // No need to reset error

    return globalError;
}


int testParameter()
{
    Parameter parameter;
    int error = 0;
    int globalError = 0;

    /* Section 1:
     * initParameterSet Function
     * and related get/set functions as a consequence of the function setup:
     * get/setMixtureAssignment,
     * getMutationSelectionState, getNumParam, getNumMixtureElements
     * get/setStdDevSynthesisRate, getCurrentStdDevSynthesisRateProposalWidth, getNumAcceptForStdDevSynthesisRate
     * getNumMutationCategories, getNumSelectionCategories
     * getMixtureElementsOfMutationCategory, getMixtureElementsOfSelectionCategory
    */

    //---------------------------------------//
    //------ initParameterSet Function ------//
    //---------------------------------------//

    /* Initialize parameter p:
    // Arguments: vector <double> stdDevSynthesisRate, unsigned numMixtures, vector <unsigned> geneAssignment,
    //           vector <vector <unsigned>> mixtureDefinitionMatrix, bool splitSer, string mutationSelectionState
    //
    // Thus, let: */
    unsigned numMixtures = 1;
    std::vector <double> stdDev(numMixtures, 1);
    unsigned numGenes = 1000;
    std::vector <unsigned> geneAssignment(numGenes);
    for (unsigned i = 0u; i < numGenes; i++)
    {
        geneAssignment[i] = 0u;
    }
    std::vector<std::vector<unsigned>> mixtureDefinitionMatrix;
    bool splitSer = true;
    std::string mutationSelectionState = Parameter::allUnique;

    parameter.initParameterSet(stdDev, numMixtures, geneAssignment, mixtureDefinitionMatrix, splitSer, mutationSelectionState);
    int initParameterSetError = 0;

    /* This call changes many variables in parameter that must now be checked.
    // Thus, unit testing is done in order of variable changed. See initParameterSet in Parameter.cpp or the table of contents above.
    // This also introduces a level of uncertainty in what may be wrong, and thus an error in the following
    // unit testing checks may be a result of the checking function or initParameterSet. */

    //------------------------------------------//
    //------ getMixtureAssignment Function------//
    //------------------------------------------//
    for (unsigned i = 0u; i < numGenes; i++)
    {
        if (parameter.getMixtureAssignment(i) != geneAssignment[i])
        {
            my_printError("Error in initParameterSet or getMixtureAssignment for index %.", i);
            my_printError(" Value should be %, but is instead %.\n", geneAssignment[i], parameter.getMixtureAssignment(i));
            error = 1;
            globalError = 1;
            initParameterSetError = 1;
        }
    }

    if (!error)
        my_print("Parameter getMixtureAssignment --- Pass\n");
    else
        error = 0; //Reset for next function.

    //-------------------------------------------//
    //------ setMixtureAssignment Functions------//
    //-------------------------------------------//
    for (unsigned i = 0u; i < numGenes; i++)
    {
        parameter.setMixtureAssignment(i, i);
        if (parameter.getMixtureAssignment(i) != i)
        {
            my_printError("Error in setMixtureAssignment for index %.", i);
            my_printError(" Value should be %, but is instead %.\n", i, parameter.getMixtureAssignment(i));
            error = 1;
            globalError = 1;
        }
    }

    if (!error)
        my_print("Parameter setMixtureAssignment --- Pass\n");
    else
        error = 0; //Reset for next function.

    //------------------------------------------------//
    //------ getMutationSelectionState Function ------//
    //------------------------------------------------//
    if (parameter.getMutationSelectionState() != mutationSelectionState)
    {
        my_printError("Error in initParameterSet or getMutationSelectionState.");
        my_printError(" Value should be %, but is instead %.\n", mutationSelectionState, parameter.getMutationSelectionState());
        globalError = 1;
        initParameterSetError = 1;
    }
    else
        my_print("Parameter getMutationSelectionState --- Pass\n");

    //----------------------------------//
    //------ getNumParam Function ------//
    //----------------------------------//

    // Because splitSer is true, by initParameterSet the numParam should be = 40.
    // TODO: Make this more dynamic / tested with other splitSer settings?

    if (parameter.getNumParam() != 40)
    {
        my_printError("Error in initParameterSet or getNumParam.");
        my_printError(" Value should be %, but is instead %.\n", 40, parameter.getNumParam());
        globalError = 1;
        initParameterSetError = 1;
    }
    else
        my_print("Parameter getNumParam --- Pass\n");

    //--------------------------------------------//
    //------ getNumMixtureElements Function ------//
    //--------------------------------------------//
    if (parameter.getNumMixtureElements() != numMixtures)
    {
        my_printError("Error in initParameterSet or getNumMixtureElements.");
        my_printError(" Value should be %, but is instead %.\n", numMixtures, parameter.getNumMixtureElements());
        globalError = 1;
        initParameterSetError = 1;
    }
    else
        my_print("Parameter getNumMixtureElements --- Pass\n");

    //--------------------------------------------//
    //------ getStdDevSynthesisRate Function------//
    //--------------------------------------------//

    // Check proposed StdDevSynthesisRate
    for (unsigned i = 0u; i < numMixtures; i++)
    {
        if (parameter.getStdDevSynthesisRate(i, 1) != stdDev[i])
        {
            my_printError("Error in initParameterSet or getStdDevSynthesisRate(proposed) for index %.", i);
            my_printError(" Value should be %, but is instead %.\n", stdDev[i], parameter.getStdDevSynthesisRate(i, 1));
            error = 1;
            globalError = 1;
            initParameterSetError = 1;
        }
    }

    // Check non-proposed StdDevSynthesisRate
    for (unsigned i = 0u; i < numMixtures; i++)
    {
        if (parameter.getStdDevSynthesisRate(i, 0) != stdDev[i])
        {
            my_printError("Error in initParameterSet or getStdDevSynthesisRate(non-proposed) for index %.", i);
            my_printError(" Value should be %, but is instead %.\n", stdDev[i], parameter.getStdDevSynthesisRate(i, 0));
            error = 1;
            globalError = 1;
            initParameterSetError = 1;
        }
    }

    if (!error)
        my_print("Parameter getStdDevSynthesisRate --- Pass\n");
    else
        error = 0; //Reset for next function.

    //--------------------------------------------//
    //------ setStdDevSynthesisRate Function------//
    //--------------------------------------------//
    for (unsigned i = 0u; i < numMixtures; i++)
    {
        parameter.setStdDevSynthesisRate(i, i);
        if (parameter.getStdDevSynthesisRate(i) != i)
        {
            my_printError("Error in setStdDevSynthesisRate for index %.", i);
            my_printError(" Value should be %, but is instead %.\n", i, parameter.getStdDevSynthesisRate(i));
            error = 1;
            globalError = 1;
        }
    }

    if (!error)
        my_print("Parameter setStdDevSynthesisRate --- Pass\n");
    else
        error = 0; //Reset for next function.

    //-----------------------------------------------------------------//
    //------ getCurrentStdDevSynthesisRateProposalWidth Function ------//
    //-----------------------------------------------------------------//

    // This value is initialized to 0.1 in initParameterSet.
    if (parameter.getCurrentStdDevSynthesisRateProposalWidth() != 0.1)
    {
        my_printError("Error in initParameterSet or getCurrentStdDevSynthesisRateProposalWidth.");
        my_printError(" Value should be %, but is instead %.\n", 0.1, parameter.getCurrentStdDevSynthesisRateProposalWidth());
        globalError = 1;
        initParameterSetError = 1;
    }
    else
        my_print("Parameter getCurrentStdDevSynthesisRateProposalWidth --- Pass\n");

    // For unit testing only.
    //---------------------------------------------------------//
    //------ getNumAcceptForStdDevSynthesisRate Function ------//
    //---------------------------------------------------------//

    // This value is initialized to 0 in initParameterSet.
    if (parameter.getNumAcceptForStdDevSynthesisRate() != 0)
    {
        my_printError("Error in initParameterSet or getNumAcceptForStdDevSynthesisRate.");
        my_printError(" Value should be %, but is instead %.\n", 0, parameter.getNumAcceptForStdDevSynthesisRate());
        globalError = 1;
        initParameterSetError = 1;
    }
    else
        my_print("Parameter getNumAcceptForStdDevSynthesisRate --- Pass\n");


    //TODO: Write getter function to unit test std_csp

    //TODO: Write getter function to unit test numAcceptForCodonSpecificParameters


    /* TODO NOTE: setNumMutationSelectionValues is accessed in initParameterSet
    // and through this function numMutationCategories and numSelectionCategories is changed.
    // This function may itself need to be tested as a middleman function.*/

    //-----------------------------------------------//
    //------ getNumMutationCategories Function ------//
    //-----------------------------------------------//

    // Because mutationSelectionState is allUnique, by initParameterSet the numMutationCategories should be = numMixtures.
    // TODO: Make this more dynamic / tested with other settings?
    if (parameter.getNumMutationCategories() != numMixtures)
    {
        my_printError("Error in initParameterSet or getNumMutationCategories.");
        my_printError(" Value should be %, but is instead %.\n", numMixtures, parameter.getNumMutationCategories());
        globalError = 1;
        initParameterSetError = 1;
    }
    else
        my_print("Parameter getNumMutationCategories --- Pass\n");

    //------------------------------------------------//
    //------ getNumSelectionCategories Function ------//
    //------------------------------------------------//

    // Because mutationSelectionState is allUnique, by initParameterSet the numSelectionCategories should be = numMixtures.
    // TODO: Make this more dynamic / tested with other settings?
    if (parameter.getNumSelectionCategories() != numMixtures)
    {
        my_printError("Error in initParameterSet or getNumSelectionCategories.");
        my_printError(" Value should be %, but is instead %.\n", numMixtures, parameter.getNumSelectionCategories());
        globalError = 1;
        initParameterSetError = 1;
    }
    else
        my_print("Parameter getNumSelectionCategories --- Pass\n");

    /* TODO NOTE: initCategoryDefinitions is accessed in initParameterSet
    // and through this function mutationIsInMixture and selectionIsInMixture is changed.
    // This function may itself need to be tested as a middleman function.*/

    //----------------------------------------------------------//
    //------ getMixtureElementsOfMutationCategory Function------//
    //----------------------------------------------------------//

    // Because mutationSelectionState is allUnique, by initParameterSet the mutationIsInMixture should be a single vector = tmp.
    // TODO: Make this more dynamic / tested with other settings?
    std::vector <unsigned> tmp;

    for (unsigned i = 0u; i < numMixtures; i++)
    {
        tmp.push_back(i);
    }

    for (unsigned i = 0u; i < numMixtures; i++)
    {
        if (parameter.getMixtureElementsOfMutationCategory(i) != tmp)
        {
            my_printError("Error in initParameterSet or getMixtureElementsOfMutationCategory for index %.\n", i);
            error = 1;
            globalError = 1;
            initParameterSetError = 1;
        }
    }

    if (!error)
        my_print("Parameter getMixtureElementsOfMutationCategory --- Pass\n");
    else
        error = 0; //Reset for next function.

    //-----------------------------------------------------------//
    //------ getMixtureElementsOfSelectionCategory Function------//
    //-----------------------------------------------------------//

    // Because mutationSelectionState is allUnique, by initParameterSet the selectionIsInMixture should be a single vector = tmp.
    // TODO: Make this more dynamic / tested with other settings?

    // Reuse tmp vector of unsigned integers defined above

    for (unsigned i = 0u; i < numMixtures; i++)
    {
        if (parameter.getMixtureElementsOfSelectionCategory(i) != tmp)
        {
            my_printError("Error in initParameterSet or getMixtureElementsOfSelectionCategory for index %.\n", i);
            error = 1;
            globalError = 1;
            initParameterSetError = 1;
        }
    }

    if (!error)
        my_print("Parameter getMixtureElementsOfSelectionCategory --- Pass\n");
    else
        error = 0; //Reset for next function.


    //TODO: Check modifications to category (a vector of MixtureDefinitions) somehow

    //TODO: Check the final four vectors of vectors that are modified in initParameterSet

    //------------------------------------------------------------------------//
    //------ End of Unit Testing for initParameterSet-related Functions ------//
    //------------------------------------------------------------------------//
    if (!initParameterSetError)
        my_print("Parameter initParameterSet --- Pass\n");

    /* Section 2:
     * InitializeSynthesisRate Function
     */

    //----------------------------------------------//
    //------ InitializeSynthesisRate Function ------//
    //----------------------------------------------//

    Genome genome;
    genome.readFasta("/Users/hollisbui/RibModelDev/data/twoMixtures/simulatedAllUniqueR.fasta");
    std::vector<double> sphi_init(numMixtures, 1);

    parameter.InitializeSynthesisRate(genome, sphi_init[0]);
    /*
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    double avg_time = 0.0;

    std::ofstream Fout;
    Fout.open("/Users/hollisbui/Gilchrist/initializeSynthesisRateTest.csv");
    if (Fout.fail())
        my_printError("Error in initializeSynthesisRateTest: Can not open file.\n");


    for (unsigned i = 0u; i < 1; i++)
    {
        start = std::chrono::steady_clock::now();
        parameter.InitializeSynthesisRate(genome, sphi_init[0]);
        end = std::chrono::steady_clock::now();

        elapsed_seconds = end - start;
        avg_time += elapsed_seconds.count();
        //my_print("Time taken: %\n", elapsed_seconds.count());
        Fout << i << "," << elapsed_seconds.count() << "\n";
    }
    avg_time /= 1;

    my_print("Time taken average: %\n", avg_time);

    Fout.close();
    */

    //ROCParameter tmp(sphi_init, numMixtures, geneAssignment, mixtureDefinitionMatrix, true, mixDef);

    return globalError;
}


int testCovarianceMatrix()
{
    CovarianceMatrix covM; //Default constructor sets numVariates to 2.
    int error = 0;
    int globalError = 0;

    //-----------------------------------------------------------//
    //------ getCovMatrix & initCovarianceMatrix Functions ------//
    //-----------------------------------------------------------//

    std::vector <double> covM2 = {0.0025, 0, 0, 0, \
                                  0, 0.0025, 0, 0, \
                                  0, 0, 0.0025, 0, \
                                  0, 0, 0, 0.0025};

    covM.initCovarianceMatrix(4);

    for (unsigned i = 0u; i < 16; i++)
    {
        // Compare, for each position of the vector of doubles, if the statically created covM2
        // equals the initialized and extracted covM
        if (covM2[i] != covM.getCovMatrix()->at(i))
        {
            my_printError("Error in getCovMatrix or initCovarianceMatrix:");
            my_printError(" at index % matrix extracted should return %", i, covM2[i]);
            my_printError(" but instead returns %.\n", covM.getCovMatrix()->at(i));
            error = 1;
            globalError = 1;
        }
    }

    if (!error)
        my_print("CovarianceMatrix getCovMatrix & initCovarianceMatrix --- Pass\n");
    else
        error = 0; //Reset for next function.

    //------------------------------//
    //------ setDiag Function ------//
    //------------------------------//
    covM.setDiag(3.14);

    covM2 = {3.14, 0, 0, 0, \
             0, 3.14, 0, 0, \
             0, 0, 3.14, 0, \
             0, 0, 0, 3.14};

    for (unsigned i = 0u; i < 16; i++)
    {
        // Compare, for each position of the vector of doubles, if the statically created covM2
        // equals the set covM
        if (covM2[i] != covM.getCovMatrix()->at(i))
        {
            my_printError("Error in setDiag:");
            my_printError(" at index % matrix extracted should return %", i, covM2[i]);
            my_printError(" but instead returns %.\n", covM.getCovMatrix()->at(i));
            error = 1;
            globalError = 1;
        }
    }

    if (!error)
        my_print("CovarianceMatrix setDiag --- Pass\n");
    else
        error = 0; //Reset for next function.

    //-----------------------------------------------------------------//
    //------ getCholeskyMatrix & choleskyDecomposition Functions ------//
    //-----------------------------------------------------------------//
    covM.choleskyDecomposition();

    // Perform Cholesky decomposition on covM2
    // (This should be the same code as used in Cholesky decomposition in CovarianceMatrix.cpp)
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < (i + 1); j++)
        {
            double LsubstractSum = 0.0;
            for (int k = 0; k < j; k++)
            {
                LsubstractSum += covM2[i * 4 + k] * covM2[j * 4 + k];
            }
            covM2[i * 4 + j] = (i == j) ? std::sqrt(covM2[i * 4 + i] - LsubstractSum) :
                               (1.0 / covM2[j * 4 + j]) * (covM2[i * 4 + j] - LsubstractSum);
        }
    }

    for (unsigned i = 0u; i < 16; i++)
    {
        // Compare, for each position of the vector of doubles, if the statically created covM2
        // equals the set covM for its Cholesky matrix
        if (covM2[i] != covM.getCholeskyMatrix()->at(i))
        {
            my_printError("Error in getCholeskyMatrix or choleskyDecomposition:");
            my_printError(" at index % matrix extracted should return %", i, covM2[i]);
            my_printError(" but instead returns %.\n", covM.getCholeskyMatrix()->at(i));
            error = 1;
            globalError = 1;
        }
    }

    if (!error)
        my_print("CovarianceMatrix getCholeskyMatrix & choleskyDecomposition --- Pass\n");
    else
        error = 0; //Reset for next function.

    //-------------------------------------//
    //------ getNumVariates Function ------//
    //-------------------------------------//
    covM.getNumVariates();

    if (covM.getNumVariates() != 4) {
        my_printError("Error in getNumVariates. Function should return 4, but returns %.\n", covM.getNumVariates());
        globalError = 1;
    }
    else
        my_print("CovarianceMatrix getNumVariates --- Pass\n");

    //TODO: Test these final two functions.
    //-------------------------------------------------------------//
    //------ transformIidNumersIntoCovaryingNumbers Function ------//
    //-------------------------------------------------------------//
    //TODO: Should implement Parameter unit testing for RandNorm before doing this!

    //Size is numCodons * (numMutationCategories + numSelectionCategories for ROCParameter
    //Each value is based on randNorm(0.0, 1.0)
    //covM.transformIidNumersIntoCovaryingNumbers(iidTest);

    //------------------------------------------------//
    //------ calculateSampleCovariance Function ------//
    //------------------------------------------------//

    return globalError;
}


/* UNIMPLEMENTED
int testTrace()
{
    Trace RFP; //initialize with 0 categories, 2 codon-specific parameter types
    Trace ROC;
    Trace FONSE;
    Trace PANSE;
    //int samples = 10;
    //int thining = 10;
    //int useSamples = 100;
    int globalError = 0;

    //-----------------------------------------//
    //------ initializeRFPTrace Function ------//
    //-----------------------------------------//
    //RFP.initializeRFPTrace();

    //-----------------------------------------//
    //------ initializeROCTrace Function ------//
    //-----------------------------------------//
    //ROC.initializeROCTrace();

    //-------------------------------------------//
    //------ initializeFONSETrace Function ------//
    //-------------------------------------------//
    //FONSE.initializeFONSETrace();

    //-------------------------------------------//
    //------ initializePANSETrace Function ------//
    //-------------------------------------------//
    //PANSE.initializePANSETrace();

    return globalError;
}
*/

/*
int testROCParameter()
{
    int globalError = 0;


    return globalError;
}

*/
int testMCMCAlgorithm()
{
	unsigned samples = 10;
	unsigned thining = 10;
    int error = 0;
    int globalError = 0;

    MCMCAlgorithm mcmc = MCMCAlgorithm(samples, thining, 10, true, true, true);

    //--------------------------------------------//
    //------ varyInitialConditions Function ------//
    //--------------------------------------------//

    //TODO: must be done before run, etc.
    //Requires running with models: ROC, RFP, FONSE.
    //Thus, unit testing can only be done after those models are unit tested.

    //--------------------------//
    //------ run Function ------//
    //--------------------------//

    //-------------------------------------------//
    //------ calculateGewekeScore Function ------//
    //-------------------------------------------//

    //---------------------------------------------------//
    //------ is/setEstimateSynthesisRate Functions ------//
    //---------------------------------------------------//
    if (!mcmc.isEstimateSynthesisRate()) {
        my_printError("Error in isEstimateSynthesisRate.");
        my_printError(" Function should return true, but returns false.\n");
        error = 1;
        globalError = 1;
    }

    mcmc.setEstimateSynthesisRate(false);
    if (mcmc.isEstimateSynthesisRate()) {
        my_printError("Error in isEstimateSynthesisRate or setEstimateSynthesisRate.");
        my_printError(" Function should return false, but returns true.\n");
        error = 1;
        globalError = 1;
    }

    mcmc.setEstimateSynthesisRate(true);
    if (!mcmc.isEstimateSynthesisRate()) {
        my_printError("Error in isEstimateSynthesisRate or setEstimateSynthesisRate.");
        my_printError(" Function should return true, but returns false.\n");
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("MCMCAlgorithm is/setEstimateSynthesisRate --- Pass\n");
    else
        error = 0; //Reset for next function.

    //------------------------------------------------------------//
    //------ is/setEstimateCodonSpecificParameter Functions ------//
    //------------------------------------------------------------//
    if (!mcmc.isEstimateCodonSpecificParameter()) {
        my_printError("Error in isEstimateCodonSpecificParameter.");
        my_printError(" Function should return true, but returns false.\n");
        error = 1;
        globalError = 1;
    }

    mcmc.setEstimateCodonSpecificParameter(false);
    if (mcmc.isEstimateCodonSpecificParameter()) {
        my_printError("Error in isEstimateCodonSpecificParameter or setEstimateCodonSpecificParameter.");
        my_printError(" Function should return false, but returns true.\n");
        error = 1;
        globalError = 1;
    }

    mcmc.setEstimateCodonSpecificParameter(true);
    if (!mcmc.isEstimateCodonSpecificParameter()) {
        my_printError("Error in isEstimateCodonSpecificParameter or setEstimateCodonSpecificParameter.");
        my_printError(" Function should return true, but returns false.\n");
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("MCMCAlgorithm is/setEstimateCodonSpecificParameter --- Pass\n");
    else
        error = 0; //Reset for next function.

    //----------------------------------------------------//
    //------ is/setEstimateHyperParameter Functions ------//
    //----------------------------------------------------//
    if (!mcmc.isEstimateHyperParameter()) {
        my_printError("Error in isEstimateHyperParameter.");
        my_printError(" Function should return true, but returns false.\n");
        error = 1;
        globalError = 1;
    }

    mcmc.setEstimateHyperParameter(false);
    if (mcmc.isEstimateHyperParameter()) {
        my_printError("Error in isEstimateHyperParameter or setEstimateHyperParameter.");
        my_printError(" Function should return false, but returns true.\n");
        error = 1;
        globalError = 1;
    }

    mcmc.setEstimateHyperParameter(true);
    if (!mcmc.isEstimateHyperParameter()) {
        my_printError("Error in isEstimateHyperParameter or setEstimateHyperParameter.");
        my_printError(" Function should return true, but returns false.\n");
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("MCMCAlgorithm is/setEstimateHyperParameter --- Pass\n");
    else
        error = 0; //Reset for next function.

    //-------------------------------------------------------//
    //------ is/setEstimateMixtureAssignment Functions ------//
    //-------------------------------------------------------//

    /* NOTE: By default, both constructors initialize estimateMixtureAssignment to true,
    // although it is not one of the arguments. */

    if (!mcmc.isEstimateMixtureAssignment()) {
        my_printError("Error in isEstimateMixtureAssignment.");
        my_printError(" Function should return true, but returns false.\n");
        error = 1;
        globalError = 1;
    }

    mcmc.setEstimateMixtureAssignment(false);
    if (mcmc.isEstimateMixtureAssignment()) {
        my_printError("Error in isEstimateMixtureAssignment or setEstimateMixtureAssignment.");
        my_printError(" Function should return false, but returns true.\n");
        error = 1;
        globalError = 1;
    }

    mcmc.setEstimateMixtureAssignment(true);
    if (!mcmc.isEstimateMixtureAssignment()) {
        my_printError("Error in isEstimateMixtureAssignment or setEstimateMixtureAssignment.");
        my_printError(" Function should return true, but returns false.\n");
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("MCMCAlgorithm is/setEstimateMixtureAssignment --- Pass\n");
    else
        error = 0; //Reset for next function.

    //-------------------------------------------//
    //------ get/setStepsToAdapt Functions ------//
    //-------------------------------------------//

    // NOTE: By default, both constructors initialize stepsToAdapt to -1
    if (mcmc.getStepsToAdapt() != -1) {
        my_printError("Error in getStepsToAdapt.");
        my_printError(" Function should return -1, but returns %.\n", mcmc.getStepsToAdapt());
        error = 1;
        globalError = 1;
    }

    mcmc.setStepsToAdapt(52);
    if (mcmc.getStepsToAdapt() != 52) {
        my_printError("Error in getStepsToAdapt or setStepsToAdapt.");
        my_printError(" Function should return 52, but returns %.\n", mcmc.getStepsToAdapt());
        error = 1;
        globalError = 1;
    }

    // Intentional error checking: Should print an error message with no change to stepsToAdapt
    mcmc.setStepsToAdapt(101);
    if (mcmc.getStepsToAdapt() != 52) {
        my_printError("Error in getStepsToAdapt or setStepsToAdapt.");
        my_printError(" Function should return 52, with no change, but returns %.\n", mcmc.getStepsToAdapt());
        error = 1;
        globalError = 1;
    }

    if (!error)
        my_print("MCMCAlgorithm get/setStepsToAdapt --- Pass\n");
    else
        error = 0; //Reset for next function.

    //--------------------------------------------//
    //------ getLogLikelihoodTrace Function ------//
    //--------------------------------------------//

    // NOTE: By default, both constructors initialize likelihoodTrace to a vector with
    // a size of samples + 1 zeroes.
    std::vector <double> likelihoodTrace = mcmc.getLogLikelihoodTrace();
    std::vector <double> tmp;
    tmp.resize(samples+1);

    if (tmp != likelihoodTrace)
    {
        my_printError("Error in getLogLikelihoodTrace. Function should return a vector of % + 1 zeroes.\n", samples);
        globalError = 1;
    }
    else
        my_print("MCMCAlgorithm getLogLikelihoodTrace --- Pass\n");

    //----------------------------------------------------//
    //------ getLogLikelihoodPosteriorMean Function ------//
    //----------------------------------------------------//
    //TODO. LikelihoodTrace is *not* set in this file, and therefore testing will
    //require implementation of models beforehand.

    return globalError;
}



//-----------------------------------------------------------------------------------------------------//
//---------------------------------------- R SECTION --------------------------------------------------//
//-----------------------------------------------------------------------------------------------------//

#ifndef STANDALONE
//---------------------------------//
//---------- RCPP Module ----------//
//---------------------------------//

RCPP_MODULE(Test_mod)
{
	function("testUtility", &testUtility);
	function("testSequenceSummary", &testSequenceSummary);
	function("testGene", &testGene);
	function("testGenome", &testGenome);
	function("testCovarianceMatrix", &testCovarianceMatrix);
	function("testMCMCAlgorithm", &testMCMCAlgorithm);
}
#endif
