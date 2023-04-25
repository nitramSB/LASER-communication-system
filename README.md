# LASER-communication-system
Experiment using a laser diode and a solar panel to transfer data between circuits.

### Block Diagram
<p align="center">
<img src="https://user-images.githubusercontent.com/13424965/206278100-a0bb01a3-e3d2-4f6c-a3a6-9395422b19d2.png" width="600" align="center">
</p>

### Physical Hardware Setup
<p align="center">
<img src="https://user-images.githubusercontent.com/13424965/206278332-89fffd58-0c2e-4c80-b9c1-bf540e2a89c0.png" width="600">![20221207_192720978_iOS](https://user-images.githubusercontent.com/13424965/206285152-4288628b-53aa-4687-8f1f-8a3b1734ccc7.jpg)

</p>

### Microcontroller Interfaces
<p align="center">
<img src="https://user-images.githubusercontent.com/13424965/206278630-8340f713-d812-40c2-9ffe-df4ac3b16904.png" width="600">
</p>

### Transmit 1 byte of data using LASER
First step of testing the LASER transmission was to get across an arbitrary signal. Therefore, I created a toggle function that toggles the LASER at 30Hz using programmable timer 0 (8 bit). Figure 1 displays the transmission and receiving signal. We observe a very close match between the two indicating that the signal waveform is not lost in transmission. Now we have verified that the electronics are working (given that the frequency is the same!).


<p align="center">
<img src="https://user-images.githubusercontent.com/13424965/206281083-5baf10fc-6f6a-4d06-8415-001456579d19.png" width="400">
</p>
The next step was to send some real data, a byte, to the LASER. This could be solved in multiple ways, but I chose to use the USART TX, since it was easy to configure. In Figure 2. you can see 2 different bytes being transmitted on the USART TX.

<p align="center">
<img src="https://user-images.githubusercontent.com/13424965/206281283-7672a1d0-6620-4fbf-8221-7fa9654de3f3.png" width="600">
</p>

The problem that I was faced now was that a ‘1’ sent via USART corresponds to a ‘0’ in signal voltage. This means that my N-channel MOSFET will not turn on the LASER. Therefore, I added a logic NOT gate to invert the signal. This inverted signal can be seen in Figure 3.

<p align="center">
<img src="https://user-images.githubusercontent.com/13424965/206281858-b69cf07b-ab4a-4979-b8f3-1868d80814b5.png" width="400">
</p>

## ... 

## Transmitter circuit made on a perfboard
<p align="center">
<img src="https://user-images.githubusercontent.com/13424965/206282980-82f01b95-04d2-47a7-ba6b-4d98b553e070.png" width="400">
</p>

## Making a custom printed circuit board (PCB) for the transmitter circuit
### Schematic
<p align="center">
<img src="https://user-images.githubusercontent.com/13424965/206284815-177658cd-5866-4c47-ab83-dc0ff3e76281.png" width="600">
</p>



### PCB Layout
<p align="center">
<img src="https://user-images.githubusercontent.com/13424965/206285862-8f793ac6-937a-43a1-8a26-a07ab52c4e0e.png" width="400">

### Manufactured PCB
<p align="center">
<img src="https://user-images.githubusercontent.com/13424965/206283372-ed85f252-fe76-4b17-b5d4-dee3c9721615.png" width="400">
</p>

### Assembled PCB
<p align="center">
<img src="https://user-images.githubusercontent.com/13424965/206285464-384a2f21-74ff-499b-9965-be6d6f216901.png" width="400">
</p>





