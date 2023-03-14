#Objectives #Aims #Outcomes #FR #NFR

| FR-1 | The transmitter and receiver shall communicate at a frequency of 925MHz|
|---|---|
| Status | draft|
| Description | The frequency band for LoRaWAN in Australia is 915-930MHz so the IoT network must operate within this range |
| Verification Method - Integration Testing | This requirement can be verified through integration testing and observing packet transmition via test application |

| FR-2 | The gateway shall receive packets from a distance of up to approximately 600m | |
| --- | --- |
| Status | draft |
| Description | LoRa communication is advertised to operate within multiple kilometers but the system will only need to operate approximately up to 600m |
| Verification Method - Integration Testing | The range of the system can be verified through integration testing by noting the distance at which packet loss occurs |

| FR-3 | The receiver shall receive packets and distinguish between at least three sensor nodes |
| --- | --- |
| Status | draft | 
| Description | The IoT system requires at least three sensor nodes to be placed along the bridge. It is therefore required that each transmitted packet contains an identifier. 
| Verification Method - Integration Testing | The identification of transmitted packets can be identified trough integration testing and observing packet transmission via a test application. | 

| FR-4 | The sensor nodes shall be powered by solar energy such that the nodes can transmit 24/7|
| --- | --- |
| Status | draft | 
| Description | The nodes need to transmit packets every hour 24/7 and hence require a solar battery system capable of supporting always-on low powered devices. |
| Verification Method - Field Testing | The current draw from the sensor nodes can be measured and the appropriate power supply can be calculated. Otherwise field testing will be required to examine how long the sensor nodes can operate for. |

| FR-5 | Each sensor node shall include an accelerometer to record analog input on the x, y and z axis |
| --- | --- |
| Status | Draft |
| Description | The accelerometers will measure the bridge's vibration. This data will be converted into digital data using Fourier transform techniques and encoded into packets. | 
| Verification Method - Integration Testing | The accelerometers will be tested in the mechanical engineering lab with a vibrating beam setup |

| NFR-1 | The sensor nodes shall be resistant to overheating and rain |
| --- | --- |
| Status | draft |
| Description | The sensor nodes will be exposed on the bridge and will therefore have to survive hot temperatures and rainfall | 
| Verification Method - Environmental Testing | The enclosure will be designed with weather proofing in mind and will undergo laboratory environmental testing |

| NFR-2 | The sensor nodes shall contain temperature and humidity sensors and transmit this data |
| --- | --- |
| Status | draft | 
| Description | Temperature and humidity data will be useful to spot any discrepancies in the data due to external environment and will be useful to field test the thermal resistance of the device enclosure. The data from these sensors will be included in the transmitted packets along with the vibration data. | 
| Verification Method - Integration Testing / Field Testing | The operational capabilities of these sensors can be examined in a lab. The functional capabilities of these sensors will need to be tested in the field. |