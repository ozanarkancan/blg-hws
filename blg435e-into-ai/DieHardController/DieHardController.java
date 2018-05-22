
import com.cyberbotics.webots.controller.Camera;
import com.cyberbotics.webots.controller.DistanceSensor;
import com.cyberbotics.webots.controller.LED;
import com.cyberbotics.webots.controller.LightSensor;

public class DieHardController extends CyberSavannahController {

    public enum State
    {
        HUNGRY, LOOKINGMATE, HUNTING, JUSTBORN;
    }
    
    public enum Role
    {
        BERRYPICKER, HUNTER, NORMAL;
    }

    public DieHardController() {
        initSensors();
        setRole(); 
    }
    
    protected void setRole()
    {
        double randValue = RandomDouble(0, 10000);
        if(randValue <= 3000){//%30
          role = Role.BERRYPICKER;
        }
        else if(randValue >= 9000)//%10
          role = Role.HUNTER;
        else
          role = Role.NORMAL;//%60
    }
    
    protected void setState(boolean control)
    {
        if(role == Role.HUNTER){
          if(state != State.JUSTBORN){
            if(state == State.HUNGRY && batterySensorGetValue() >= 140)
              state = State.HUNTING;
            else if(state == State.HUNTING && batterySensorGetValue() <= 100)
              state = State.HUNGRY;
          }
          else
          {
            if(state == State.JUSTBORN && control && batterySensorGetValue() >= 140)//Hunter at the begining of simulation
              state = State.HUNTING;
            else if(state == State.JUSTBORN && control && batterySensorGetValue() <= 100)//Baby hunter
              state = State.HUNGRY;
          }
        }
        else
        {
          if(role == Role.BERRYPICKER){
            if(state == State.JUSTBORN && control)
              state = State.HUNGRY;
          }
          else//NORMAL
          {
            if(state != State.JUSTBORN)
            {
              if(batterySensorGetValue() >= 150)
                state = State.LOOKINGMATE;
              else
                state = State.HUNGRY;
            }
            else
            {
              if(state == State.JUSTBORN && control && batterySensorGetValue() >= 150)//Normal robot at the begining of simulation
                state = State.LOOKINGMATE;
              else if(state == State.JUSTBORN && control && batterySensorGetValue() <= 100)//Baby normal robot
                state = State.HUNGRY;              
            }
          }
        }
    } 
    
    /**
    * Initialises e-puck sensors, LEDs
    */
    protected void initSensors() {
        String ledText = "led";//led is the led sensor prefix
        String dsText = "ps";//ps is the distance sensor prefix
        String lsText = "ls";//ls is the light sensor prefix
        String fsText = "fs";//fs is the floor sensor prefix
        for (int i = 0; i < 8; i++) {//for each sensor
            leds[i] = getLED(ledText + i);//getLED and assign that sensor to the position in the list (0-8)
            distanceSensors[i] = getDistanceSensor(dsText + i);//repeat with distance sensors
            lightSensors[i] = getLightSensor(lsText + i);//repeat with light sensorss
            distanceSensors[i].enable((int)getBasicTimeStep());//enable sensors
            lightSensors[i].enable((int)getBasicTimeStep());
        }
        for (int j = 0; j < 3; j++) {
            floorSensors[j] = getDistanceSensor(fsText + j);
            floorSensors[j].enable((int)getBasicTimeStep());
        }
        batterySensorEnable(4 * (int)getBasicTimeStep());//enable the battery sensor after 4 time steps
        camera = getCamera("camera");
        camera.enable((int)getBasicTimeStep() * 4);
        cameraWidth = camera.getWidth();
        cameraHeight = camera.getHeight();
    }
    Camera camera;
    LED[] leds = new LED[8];
    DistanceSensor[] distanceSensors = new DistanceSensor[8];
    DistanceSensor[] floorSensors = new DistanceSensor[3];
    LightSensor[] lightSensors = new LightSensor[8];
    protected int foodPixelCounter = 0, matePixelCounter = 0, robotPixelCounter = 0;
    protected int cameraWidth = 0,
            cameraHeight = 0;
    protected boolean leftObstacle = false, rightObstacle = false, seenFood = false, seenMate = false, seenRobot = false,
    backwardObstacle = false, turnback = false, justborn = false;
    protected double randInt = (int) RandomDouble(-100, 100);
    protected double second = (15.625 * (int)getBasicTimeStep());
    protected double movementTimer = 0.0,
            behaviourTimer = 0.0,
            turnTimer = 0.0,
            leftMovement = 0.0,
            rightMovement = 0.0,
            fieldOfView = 0.0,
            displayTimer = 0.0,
            leftSpeed = 0,
            rightSpeed = 0,
            turnBackTimer = 0.0;
    protected int behaviour = 0,
            previousMateDeltaX = 0, previousFoodDeltaX = 0, previousRobotDeltaX = 0,
            xPositionFoodBlob = 0, yPositionFoodBlob = 0,
            xPositionMateBlob = 0, yPositionMateBlob = 0,
            xPositionRobotBlob = 0, yPositionRobotBlob = 0;
       
    protected State state = State.JUSTBORN;//dafault value
    protected Role role;

    /**
     * Sample run method that uses the e-puck's battery as a check for the
     * behaviours. If the Investigate method returns true when applied to mating
     * or eating (dependent on energy), this in turn will update the emitter
     * string, to indicate the state of behaviour to the Simulation Manager.
     */
      protected void csRun() {
        if(state == State.JUSTBORN)
        {
          blinkLed();
          leftSpeed = 0;
          rightSpeed = 0;
          movementTimer += (int)getBasicTimeStep();
          return;
        }
        setState(false);
        if(role == Role.HUNTER)
        {
           CollisionAvoidance(true);
           HunterMove();
           if(state == State.HUNTING)
           {
              ReadyToMate();//Turn on leds
              robotPixelCounter = LookForRobot();
              matePixelCounter = LookForMate();
              if(robotPixelCounter > 1 && matePixelCounter == 0)
              {
                CollisionAvoidance(false);
                leftSpeed = 850;
                rightSpeed = 850;
                seenRobot = Investigate(xPositionRobotBlob, yPositionRobotBlob, robotPixelCounter, previousRobotDeltaX);
                if (seenRobot) {
                   if(batterySensorGetValue() >= 160)
                     mate();//If another robot catch it and calling mate
                }
              }
              
           }
           else//HUNGRY
           {
             ReadyToEat();
             foodPixelCounter = LookForFood();
             if (foodPixelCounter > 1) {
                CollisionAvoidance(false);
                leftSpeed = 750;
                rightSpeed = 750;
                seenFood = Investigate(xPositionFoodBlob, yPositionFoodBlob, foodPixelCounter, previousFoodDeltaX);
                if (seenFood) {
                    eat();
                }
              }
           }
        }
        else
        {
            if(role == Role.BERRYPICKER)
            {
              if(!CheckBackward(true) && !turnback){
                CollisionAvoidance(true);
                ReadyToEat();
                foodPixelCounter = LookForFood();
                if (foodPixelCounter > 1) {
                  CollisionAvoidance(false);
                  leftSpeed = 750;
                  rightSpeed = 750;
                  seenFood = Investigate(xPositionFoodBlob, yPositionFoodBlob, foodPixelCounter, previousFoodDeltaX);
                  if (seenFood) {
                    if(batterySensorGetValue() <= 190)//don't eat until battery drops under 190
                      eat();
                  }
                }
              }
              else
                turnBack();//There might be new berry behind the robot
            }
            else//Normal
            {
              if(!CheckBackward(true) && !turnback){
                Wandering();
                CollisionAvoidance(true);
                if (batterySensorGetValue() < 200 && batterySensorGetValue() > 150) {
                  ReadyToMate();
                  matePixelCounter = LookForMate();
                  if (matePixelCounter > 1) {
                    CollisionAvoidance(false);
                    leftSpeed = 500;
                    rightSpeed = 500;
                    seenMate = Investigate(xPositionMateBlob, yPositionMateBlob, matePixelCounter, previousMateDeltaX);
                    if (seenMate) {
                      mate();
                    }
                  }
                }
                else if (batterySensorGetValue() <= 150) {
                  ReadyToEat();
                  foodPixelCounter = LookForFood();
                  if (foodPixelCounter > 1) {
                    CollisionAvoidance(false);
                    leftSpeed = 750;
                    rightSpeed = 750;
                    seenFood = Investigate(xPositionFoodBlob, yPositionFoodBlob, foodPixelCounter, previousFoodDeltaX);
                    if (seenFood) {
                        eat();
                    }
                  }
                }
              }
              else{
                ReadyToMate();
                turnBack();
              }
            }
        }
        setSpeed(leftSpeed, rightSpeed);
        movementTimer += (int)getBasicTimeStep();
    }
    
    //BEHAVIOUR SETS
    
    protected void blinkLed()
    {
      if (movementTimer < 1 * second || (movementTimer > 2 * second && movementTimer < 3 * second)) {
        leds[0].set(1);
      }
      else if(movementTimer >= 1 * second && movementTimer <= 2 * second)
      {
        leds[0].set(0);
      }
      else if(movementTimer >= 3 * second)
      {
        leds[0].set(0);
        setState(true);
        movementTimer = 0;
      }
    }
    
    protected void turnBack()
    {
        if(turnBackTimer == 0)
          turnBackTimer = movementTimer;
        else
        {
          if(Math.abs(turnBackTimer - movementTimer) < 0.8 * second )
          {
            leftSpeed = 800;
            rightSpeed = -800;
          }
          else
          {
            turnback = false;
            turnBackTimer = 0;
          }
        }
    }
    
    protected void HunterMove()
    {
      //turn left
      if(movementTimer<4*second
          || (movementTimer>=23*second && movementTimer<27*second)) {
         leftSpeed = -100;
         rightSpeed = 100;
      }
      //turnRight
      else if(movementTimer<8*second && movementTimer>=4*second
        || (movementTimer>=27*second && movementTimer<31*second)) {
         leftSpeed =200;
         rightSpeed = -200;
      }
      //turn left, align center
      else if(movementTimer>=8*second && movementTimer<12*second
          || (movementTimer>=31*second && movementTimer<35*second)) {
        leftSpeed = -100;
        rightSpeed = 100;
      }
      //move ahead
      else if(movementTimer>=12*second && movementTimer<16*second
        || (movementTimer>=35*second && movementTimer<39*second)) {
        leftSpeed = 800;
        rightSpeed = 800;
      }
      //turn left
      else if(movementTimer>=16*second && movementTimer<19*second) {
        leftSpeed = -110;
        rightSpeed = 110;
      }
      //move ahead
      else if(movementTimer>=19*second && movementTimer<23*second) {
        leftSpeed = 600;
        rightSpeed = 600;
      }
      //reset time
      else if(movementTimer >= 46 * second) {
        movementTimer = 0;
      }
    }
    
    /*
    protected void waitForFeeding()
    {
      //check time issues
      if(batterySensorGetValue() > 80)
      {
          ReadyToEat();//You are on your feet
          justborn = false;
      }
    }*/
    
    //Mating
    /**
     * Returns true if battery level is above 150. Turns on all LEDs to indicate
     * preference to mate
     *
     * @return boolean true is battery is greater than 150
     */
    protected boolean ReadyToMate() {
        if (batterySensorGetValue() > 150) {                        //if the energy level is greater than 50
            //this robot wants to mate
            leds[0].set(0);
            for (int i = 1; i < leds.length; i = i + 2) {
                leds[i].set(1);
            }
            return true;
        }
        return false;
    }
    //Feeding

    /**
     * Returns true if battery level is below 150. Turns off all LEDs to
     * indicate preference not to mate
     *
     * @return boolean true if battery is less than 150
     */
    protected boolean ReadyToEat() {
        if (batterySensorGetValue() < 150) {                        //if the energy level is less than 50
            //this robot wants to eat
            for (int i = 1; i < leds.length; i++) {
                leds[i].set(0);
            }
            return true;
        }
        return false;
    }
    //Wandering

    /**
     * Uses timer to generate different movement speeds to be used in SetSpeed.
     */
    protected void Wandering() {
        if (movementTimer < 2.5 * second) {
            if (randInt % 2 == 0) {
                leftSpeed = -250;
                rightSpeed = 250;
            } else {
                leftSpeed = 250;
                rightSpeed = -250;
            }
        } else if (movementTimer >= 2.5 * second && movementTimer < 10 * second) {
            leftSpeed = RandomDouble(0, 1000);
            rightSpeed = RandomDouble(0, 1000);
        } else if (movementTimer >= 10 * second && movementTimer < 15 * second) {
            leftSpeed = 750;
            rightSpeed = 750;
        } else if (movementTimer >= 15 * second && movementTimer < 17 * second) {
            leftSpeed = -250;
            rightSpeed = -250;
        } else if (movementTimer >= 17 * second) {
            movementTimer = 0;
        }
    }

    /**
     * Method to allow the e-puck to avoid obstacles and collisions. Can be
     * switched on and off.
     *
     * @param activationSwitch
     */
    protected void CollisionAvoidance(boolean activationSwitch) {
        if (activationSwitch) {
            leftObstacle =
                    distanceSensors[0].getValue() > 100.0
                    || distanceSensors[1].getValue() > 100.0
                    || distanceSensors[2].getValue() > 100.0;
            rightObstacle =
                    distanceSensors[5].getValue() > 100.0
                    || distanceSensors[6].getValue() > 100.0
                    || distanceSensors[7].getValue() > 100.0;
            if (rightObstacle) {//is there an obstacle on the right
                leftSpeed = 200;
                rightSpeed = -200;//turn left
            } else if (leftObstacle) {//if there is a blockage on the left
                leftSpeed = -200;
                rightSpeed = 200;//turn right
            }
        }
    }
    
    protected boolean CheckBackward(boolean activationSwitch)
    {
      if(activationSwitch)
      {
            backwardObstacle = distanceSensors[3].getValue() > 300 ||
                      distanceSensors[4].getValue() > 300;
            if(backwardObstacle)
            {
                turnback = true;
                return true;
            }
      }
      return false;
    }

    /**
     * Uses the camera to return the number of coloured pixel clustered
     * together. Based upon the RatLife contestant controller's pixel
     * recognition method.
     *
     * @return int value of the number of pixels of the representative colour
     */
    protected int LookForFood() {
        int[] image = camera.getImage();                //get image - credit to Rot0.java controller for colour blob recognition
        xPositionFoodBlob = 0;                                      //X position of blob
        yPositionFoodBlob = 0;                                      //y position of blob
        int blobs = 0;                                  //number of blobs
        for (int w = 0; w < cameraWidth; w++) {
            for (int h = 0; h < cameraHeight; h++) {
                int pixel = image[h * cameraWidth + w]; //break image down into pixels
                if (Camera.pixelGetRed(pixel) > 248) {  //look for red pixels
                    xPositionFoodBlob += w;                         //position is incremented by width iterator value
                    yPositionFoodBlob += h;                         //position is incremented by height iterator value
                    blobs++;                            //increment blob count
                }
            }
        }
        return blobs;                                   //return to main
    }
    
    protected int LookForRobot()
    {
        int[] image = camera.getImage();                //get image - credit to Rot0.java controller for colour blob recognition
        xPositionRobotBlob = 0;                                      //X position of blob
        yPositionRobotBlob = 0;                                      //y position of blob
        int blobs = 0;                                  //number of blobs
        for (int w = 0; w < cameraWidth; w++) {
            for (int h = 0; h < cameraHeight; h++) {
                int pixel = image[h * cameraWidth + w]; //break image down into pixels
                if (Camera.pixelGetRed(pixel)==Camera.pixelGetBlue(pixel) &&
                      Camera.pixelGetBlue(pixel)==Camera.pixelGetGreen(pixel) &&
                      Camera.pixelGetRed(pixel)<150 && Camera.pixelGetRed(pixel)>100) {  //look for red pixels
                    xPositionRobotBlob += w;                         //position is incremented by width iterator value
                    yPositionRobotBlob += h;                         //position is incremented by height iterator value
                    blobs++;                            //increment blob count
                }
            }
        }
        return blobs;    
    }

    /**
     * Uses the camera to return the number of coloured pixel clustered
     * together. Based upon the RatLife contestant controller's pixel
     * recognition method.
     *
     * @return int value of the number of pixels of the representative colour
     */
    protected int LookForMate() {
        int[] image = camera.getImage();                //get image
        xPositionMateBlob = 0;                                      //X position of blob
        yPositionMateBlob = 0;                                      //y position of blob
        int blobs = 0;                                  //number of blobs
        for (int w =20; w < cameraWidth - 20; w++) {
            for (int h = 0; h < cameraHeight; h++) {
                int pixel = image[h * cameraWidth + w];
                int pixelLeftNeighbour = image[h * cameraWidth + w - 20];
                int pixelRightNeighbour = image[h * cameraWidth + w + 20];  //break image down into pixels
                if (Camera.pixelGetGreen(pixel) > 200 && 
                Camera.pixelGetGreen(pixelLeftNeighbour) < 150 &&
                Camera.pixelGetGreen(pixelRightNeighbour) < 150) {  //look for green pixels
                    xPositionMateBlob += w;                         //position is incremented by width iterator value
                    yPositionMateBlob += h;                         //position is incremented by height iterator value
                    blobs++;                            //increment blob count
                }
            }
        }
        return blobs;                                   //return to main
    }
    
    /*protected int LookForChild()
    {
        int[] image = camera.getImage();                //get image
        xPositionMateBlob = 0;                                      //X position of blob
        yPositionMateBlob = 0;                                      //y position of blob
        int blobs = 0;                                  //number of blobs
        for (int w =20; w < cameraWidth - 20; w++) {
            for (int h = 0; h < cameraHeight; h++) {
                int pixel = image[h * cameraWidth + w];
                int pixelLeftNeighbour = image[h * cameraWidth + w - 20];
                int pixelRightNeighbour = image[h * cameraWidth + w + 20];  //break image down into pixels
                if (Camera.pixelGetGreen(pixel) > 200 && 
                Camera.pixelGetGreen(pixelLeftNeighbour) > 200 &&
                Camera.pixelGetGreen(pixelRightNeighbour) > 200) {  //look for green pixels
                    xPositionMateBlob += w;                         //position is incremented by width iterator value
                    yPositionMateBlob += h;                         //position is incremented by height iterator value
                    blobs++;                            //increment blob count
                }
            }
        }
        return blobs;
    }*/

    /**
     * Adapted from RatsLife contestant controller. Moves the e-puck so that the
     * pixel cluster is directly in the middle of the camera viewport
     *
     * @param xPos - x position of the pixel cluster relative to the camera
     * viewport
     * @param yPos - y position of the pixel cluster relative to the camera
     * viewport
     * @param blobCount - number of pixels of the required colour
     * @param prevDelta - previous delta value of the x position to make
     * adjustments to the e-puck's position
     * @return boolean - true if the e-pcuk has spotted an object of interest
     * (mate or berry)
     */
    protected boolean Investigate(int xPos, int yPos, int blobCount, int prevDelta) {
        if (blobCount > 2) {
            xPos /= blobCount;
            yPos /= blobCount;
            int delta = (xPos - cameraWidth / 2) * 10;
            if (prevDelta != delta) {
                leftSpeed = (2 * delta) + 100;
                rightSpeed = (-2 * delta) + 100;
                prevDelta = delta;
            }
            return true;
        }
        return false;
    }

    /**
     * Generates a random double value
     *
     * @param rangeStart - the minimum value of the range
     * @param rangeEnd - the maximum value of the range
     * @return random double value within the declared range
     */
    protected double RandomDouble(double rangeStart, double rangeEnd) {
        return (rangeStart + (Math.random() * (rangeEnd - rangeStart)));
    }

    public static void main(String[] args) {
        try {
            DieHardController controller = new DieHardController();
            controller.run();
        } catch (Exception e) {
            e.printStackTrace();
            e.getCause().toString();
        }
    }
}
