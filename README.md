# Enigma Simulator #

A simulator for the German Enigma Machines used during World War II written in C++. This simulation currently emulates the three wheels used by the Wehrmacht Enigma I introduced in 1930 and the two additional wheels introduced by the German Army for the M3 Enigma. It also supports the three varieties of reflector employed by these two machines that had set wiring patterns.

### Wheel Specifications ###

*Note:* The mapping specifications used in the code and shown below are taken from this [Wikipedia article.] (http://en.wikipedia.org/wiki/Enigma_rotor_details#Rotor_wiring_tables)

Wheels I - III come from the Wehrmacht Enigma and Wheels IV - V were introduced in the M3 Enigma in 1938. These wheels perform encryption by applying the mapping found in the second column to the input the wheel receives. This input will vary from wheel to wheel, but the difference between the wheel's current orientation (i.e. what letter is on top) and the output of the mapping will remain constant as it passes from wheel to wheel. For the first wheel, the input is different. The steckerboard cannot move, thus the A on the steckerboard will always map to the letter at the top of the first wheel, B to the letter after that, and so on down the line. To clarify, let's show an example:

1. We'll use two wheels: III passing information to II. Let's say wheel III is at position F and II is at position H.
2. We'll also say that wheel III is the rightmost wheel and thus the first to get input. Let's say the letter we're going to translate is B. 
3. Since B is the first letter after A, it maps to the first letter after the current position fo the wheel, G.
4. We now apply the mapping of wheel III to the letter G. From the table below, we can see that G maps to C.
5. Since C is 3 letters in front of wheel III's current position (F), the next wheel's input will be the letter three letters in front of its current position.
6. The next wheel is wheel II currently at position H, so its input is E, the letter 3 places before H.
7. We now apply wheel II's mapping to the letter E and arrive at S.
8. Since S is 11 letters ahead of the current wheel position (H), the input to the next wheel will be the letter 11 places after its current position.

<table>
  <tr>
    <td>Wheel Number</td>
    <td>ABCDEFGHIJKLMNOPQRSTUVWXYZ</td>
    <td>Turnover Point</td>
  </tr>
  <tr>
    <td>I</td>
    <td>EKMFLGDQVZNTOWYHXUSPAIBRCJ</td>
    <td>R</td>
  </tr>
  <tr>
    <td>II</td>
    <td>AJDKSIRUXBLHWTMCQGZNPYFVOE</td>
    <td>F</td>
  </tr>
  <tr>
    <td>III</td>
    <td>BDFHJLCPRTXVZNYEIWGAKMUSQO</td>
    <td>W</td>
  </tr>
  <tr>
    <td>IV</td>
    <td>ESOVPZJAYQUIRHXLNFTGKDCMWB</td>
    <td>K</td>
  </tr>
  <tr>
    <td>V</td>
    <td>VZBRGITYUPSDNHLXAWMJQOFECK</td>
    <td>A</td>
  </tr>
</table>

### Reflector Specification ###
*Note:* Like before, the wiring specifications come from [here.] (http://en.wikipedia.org/wiki/Enigma_rotor_details#Rotor_wiring_tables)

These three reflector versions are the most common reflectors used. A and B were the most commonly used, with B replacing A in 1937. Version C appeared in 1940. The reflector is the Enigma's fourth wheel. However, it does not rotate like the other three, and its job was to "reflect" the electrical curent back through the wheels in the opposite direction. The process of reflection is similar to that of passing a letter through the wheels like described above. Since the reflector does not move, the A of the reflector will always line up with the letter on the top of the last wheel. Like before, we will provide an example:

1. We'll use reflector B, just for fun. We'll say the input we recieve is the letter 5 before the current position of the last wheel.
2. The letter A will always line up with the position of the last wheel, so the input letter the reflect recieves is 5 letters before A which correponds to the letter V.
3. We now apply the mapping of reflector B to the letter V and get the letter W.
4. Since W is 4 letters before A, the input letter the reflector sends back to the last wheel will be 4 letters before the wheel's current position.

<table>
  <tr>
    <td>Reflector Version</td>
    <td>ABCDEFGHIJKLMNOPQRSTUVWXYZ</td>
  </tr>
  <tr>
    <td>A</td>
    <td>EJMZALYXVBWFCRQUONTSPIKHGD</td>
  </tr>
  <tr>
    <td>B</td>
    <td>YRUHQSLDPXNGOKMIEBFZCWVJAT</td>
  </tr>
  <tr>
    <td>C</td>
    <td>FVPJIAOYEDRZXWGCTKUQSBNMHL</td>
  </tr>
</table>

#Obtaining and building the code#
Either download the code as a zip file and extract it to your desired location or clone the git repository. Once this is done, you can simply type `make` in your terminal of choice to build the simulator.
