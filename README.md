# Gust
An interactive pinwheel installation.

As a user approaches the installation, they'll use their breath to spin a miniature pinwheel. As the object turns, they'll discover they're powering a vast field of larger than life pinwheels with this same breath.


# I2C
Multiple Arduinos are connected in a master slave pattern using the I2C protocol. The master is responsible for detecting input, determining motor speed and pinwheel order. The slaves are used to increase the quantity of PWM outputs.

A custom communication method is used from the master, taking the form of `Arduino ID:Motor Output:Motor Value` or `1:7:255`. Arduino IDs are arbitrary and named in the code base as `0, 1, 2`.
