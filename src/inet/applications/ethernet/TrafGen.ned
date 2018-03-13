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

package ifanet.inet.applications.ethernet;
import ifanet.inet.applications.contract.IHostApp;

simple TrafGen like IHostApp
{
	parameters:
	    double startTime @unit(s) = default(0s);
	    double stopTime @unit(s) = default(-1s);
	    volatile double sendInterval @unit(s);
	    volatile int numPacketsPerBurst = default(1);
	    volatile int packetLength @unit(B);
	    
	    @signal[sentPk](type=cPacket);
	    @statistic[sentPk](title="packets sent";source=sentPk;record=count;interpolationmode=none);	
	    
	    @class(TrafGen);
	gates:
	    //input appIn;
	    output appOut;	        
}
