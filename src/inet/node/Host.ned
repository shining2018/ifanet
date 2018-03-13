//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package ifanet.inet.node;
import ifanet.inet.mobility.contract.IMobility;
import ifanet.inet.linklayer.contract.IHostMac;
import ifanet.inet.applications.contract.IHostApp;
import ifanet.inet.common.queue.DropTailQueue;
import ifanet.inet.physicallayer.contract.IHostRadio;

module Host
{
    parameters:
        @display("i=device/uav_vs");
        string mobilityType = default("StationaryMobility");
        string appType = default("");
        string macType = default("");
        string radioType = default("");
        @networkNode();

    gates:
        input in @directIn;

    submodules:
        mobility: <mobilityType> like IMobility;
        app: <appType> like IHostApp {

            @display("p=117,38");
        }

        mac: <macType> like IHostMac {

            @display("p=117,234");
        }

        pkQueue: DropTailQueue {
            @display("p=117,130");
        }
        reTransQueue: DropTailQueue {
            @display("p=228,130");
        }
        radio: <radioType> like IHostRadio {

            @display("p=117,327");
        }

    connections:
        app.appOut --> pkQueue.in;
        pkQueue.out --> mac.upperLayerInPkQueue;
        reTransQueue.out --> mac.upperLayerInReTransQueue;
        mac.radioInOut <--> radio.macInOut;
        in --> radio.radioIn;
        radio.reTransQueueOut --> reTransQueue.in;

}
