// Copyright 2009-2025 NTESS. Under the terms
// of Contract DE-NA0003525 with NTESS, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2009-2025, NTESS
// All rights reserved.
//
// Portions are copyright of other developers:
// See the file CONTRIBUTORS.TXT in the top level directory
// of the distribution for more information.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

// Copyright 2016 IBM Corporation

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef C_BANKSTATEPRECHARGE_HPP
#define C_BANKSTATEPRECHARGE_HPP

// C++ includes
#include <memory>
#include <list>

// CramSim includes
#include "c_BankState.hpp"
#include "c_BankCommand.hpp"
#include "c_BankInfo.hpp"

namespace SST {
namespace CramSim {

class c_BankStateIdle;

class c_BankStatePrecharge: public c_BankState {

public:

    c_BankStatePrecharge(std::map<std::string, unsigned>* x_bankParams);
    ~c_BankStatePrecharge();

    virtual void handleCommand(c_BankInfo* x_bank, c_BankCommand* x_bankCommandPtr, SimTime_t x_cycle);

    virtual void clockTic(c_BankInfo* x_bank, SimTime_t x_cycle);

    virtual void enter(c_BankInfo* x_bank,
            c_BankState* x_prevState, c_BankCommand* x_cmdPtr, SimTime_t x_cycle);

    virtual std::list<e_BankCommandType> getAllowedCommands();

    virtual bool isCommandAllowed(c_BankCommand* x_cmdPtr,
            c_BankInfo* x_bankPtr);

private:
    SimTime_t m_timer; //<! counts down to 0. when 0, changes state to IDLE automatically. is reset to ?? at state entry.
    c_BankCommand* m_receivedCommandPtr; //<! pointer to a received command
    c_BankCommand* m_prevCommandPtr;
    std::list<e_BankCommandType> m_allowedCommands;

};

}
}
#endif // C_BANKSTATEPRECHARGE_HPP
