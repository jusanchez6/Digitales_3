import time
from lib import seg_7, detect_pwm, duty_cycle, frequency


def main():
    # Add your main code logic here
    global duty_cycle, frequency
    seg_7.init()
    detect_pwm.init_pwm_detection()

    while True:
        print("Duty Cycle:", duty_cycle, "%")
        print("Frequency:", frequency, "Hz")
       



if __name__ == "__main__":
    main()

