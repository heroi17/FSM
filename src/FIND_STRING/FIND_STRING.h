#pragma once
#include "../FSM_CLASS/FSM_CLASS.h"
#include <vector>
const string ASCI_ALPHABET_ENGLIS_ = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";

bool IsStringIn(string text, string substring, string alphabet=ASCI_ALPHABET_ENGLIS_);



FSM<string, char> generateAutomatStrIn(string substring, string alphabet);

