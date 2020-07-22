# Smart Door Lock

<br/>

## Check attribute

1. Is Locked? / Unlocked?
2. Is Open?
3. Is Right Password?
4. Is Over Count Input?
5. Is Detected?

<br/>

## Loop

* Check the **lock_status**, **is it locked** or **unlocked**.

  1. if **lock_status** is **unlocked**

     <br/>

     * Check the **open_status** **is closed** or **opened**.

       1. if **open_status** is **closed** (Judge by **distance** with Ultrasonic sensor)

          * melody (3) - when the door is closed melody
          * Turn off the Green LED
          * Turn on the Red LED
          * Servo motor write (180) - change **lock_status** to locked
          * melody (2) - when the door is locked melody

       2. if **open_status** is opened

          * nothing to do

          <br/>

  2. if **lock_status** is **locked**

     <br/>

     * Check the **status_input** is **available**

       1. if **status_input** is **available**

          * input password from keypad
            * print to LCD
          * input password from bluetooth controller
            * print to LCD

          <br/>

          * Check the **password** is **collect**

            1. if **password** is **collect**

               * Turn off the Red LED
               * Turn on the Green LED
               * Servo motor write (90) - change **lock_status** to unlocked
               * melody (1) - when the door is unlocked melody

            2. if **password** is **wrong**

               * melody (4) - when the password is wrong melody
               * wrong count++

               <br/>

               * Check the input count
                 1. if number of **inputs** are more than **3 counts**
                    * Make the Red LED to blink
                    * melody (5) - when the password is wrong more than 3 times
                    * Turn on the Red LED
                    * count reset to zero
                 2. if number of **inputs** are less than **3 counts**
                    * nothing to do

          <br/>

       2. if **status_input** is **not available**

          * nothing to do

* Check the **detected_status**, is it detected

  1. if **detected_status** is true
     * melody(6) - when someone come or something has been delivered melody
  2. if **detected_status** is false
     * nothing to do