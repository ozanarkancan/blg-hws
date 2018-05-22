#include "grammar.h"

using namespace std;

Grammar::Grammar()
{
    startSymbol = "S";

    terminals.push_back("[");
    terminals.push_back("]");
    terminals.push_back("(");
    terminals.push_back(")");
    terminals.push_back("=");
    terminals.push_back(";");
    terminals.push_back("id");
    terminals.push_back("$");

    nonterminals.push_back("S");
    nonterminals.push_back("Deyimler");
    nonterminals.push_back("Deyim");
    nonterminals.push_back("Degisken");
    nonterminals.push_back("Ifade");

    deque<Rule> rulesForS;
    deque<Rule> rulesForDeyimler;
    deque<Rule> rulesForDeyim;
    deque<Rule> rulesForDegisken;
    deque<Rule> rulesForIfade;

    Rule r0("S", "Deyimler$", 0);
    rulesForS.push_back(r0);

    Rule r1("Deyimler", "Deyim", 1);
    Rule r2("Deyimler", "Deyimler;Deyim", 2);
    rulesForDeyimler.push_back(r1);
    rulesForDeyimler.push_back(r2);

    Rule r3("Deyim", "Degisken=Ifade", 3);
    rulesForDeyim.push_back(r3);

    Rule r4("Degisken", "id[Ifade]", 4);
    Rule r5("Degisken", "id", 5);
    rulesForDegisken.push_back(r4);
    rulesForDegisken.push_back(r5);

    Rule r6("Ifade", "id", 6);
    Rule r7("Ifade", "(Ifade)", 7);
    rulesForIfade.push_back(r6);
    rulesForIfade.push_back(r7);

    rules["S"] = rulesForS;
    rules["Deyimler"] = rulesForDeyimler;
    rules["Deyim"] = rulesForDeyim;
    rules["Degisken"] = rulesForDegisken;
    rules["Ifade"] = rulesForIfade;
}

Grammar::~Grammar()
{
    terminals.clear();
    nonterminals.clear();
    rules.clear();
}
