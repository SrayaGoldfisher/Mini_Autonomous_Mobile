### Benewake TF-Luna
===================================
The `TF-Luna <http://en.benewake.com/product/detail/5e1c1fd04d839408076b6255.html>`__ has a range of 8m indoor, and 3m outdoor and weighs 5g.

More details on both these lidar can be found in the `benewake.com's downloads area <http://en.benewake.com/download>`__

.. image:: /res/wuliu/images/157893742712833213.jpg

## note
   Support for this sensor is available in Copter-3.6 (and higher) and Rover-3.4 (and higher)
   For a serial connection you can use any spare Serial/UART port.  The diagram below shows how to connect to SERIAL4.

.. image:: ../../../images/benewake-tf02-pixhawk.png


## Connecting to the Autopilot
If the SERIAL4/5 port on a Pixhawk is being used then the following parameters should be set for the first rangefinder:

- `SERIAL4_PROTOCOL <https://ardupilot.org/copter/docs/parameters.html#serial4-protocol>` = 9 (Lidar)
- `SERIAL4_BAUD <https://ardupilot.org/copter/docs/parameters.html#serial4-baud>` = 115 (115200 baud)
- `RNGFND1_TYPE <https://ardupilot.org/copter/docs/parameters.html#rngfnd1-type>` = 20
- `RNGFND1_MIN_CM <https://ardupilot.org/copter/docs/parameters.html#rngfnd1-min-cm>` = 10
- `RNGFND1_MAX_CM <https://ardupilot.org/copter/docs/parameters.html#rngfnd1-max-cm>`: Use **800** for indoor, **300** for outdoor. *This is the distance in centimeters that the rangefinder can reliably read.*
- `RNGFND1_GNDCLEAR <https://ardupilot.org/copter/docs/parameters.html#rngfnd1-gndclear>` = 10 *or more accurately the distance in centimetres from the range finder to the ground when the vehicle is landed.  This value depends on how you have mounted the rangefinder.*

If instead the Telem2 port was used then the serial parameters listed above should instead be:

-  :ref:`SERIAL2_PROTOCOL <https://ardupilot.org/copter/docs/parameters.html#serial2-protocol>` = 9
-  :ref:`SERIAL2_BAUD <https://ardupilot.org/copter/docs/parameters.html#serial2-baud>` = 115


## Testing the sensor
Distances read by the sensor can be seen in the Mission Planner's Flight
Data screen's Status tab. Look closely for "sonarrange".

.. image:: ../../../images/mp_rangefinder_lidarlite_testing.jpg
    :target: ../_images/mp_rangefinder_lidarlite_testing.jpg
