## Python code for reading MPU6050 data and calculating offset values
import csv
import numpy as np
import matplotlib.pyplot as plt

accel_factor = ((2.0**15.0)-1.0)/2.0 # conversion using sensitivity (+- 2g)
gyro_factor = ((2.0**15.0)-1.0)/250.0 # conversion using sensitivity (250 deg/sec)
time_vec = np.divide(time_vec,1000000.0) # correct for microseconds -> seconds
samp_rate = len(time_vec)/(time_vec[-1]-time_vec[0]) # psuedo sample rate

plt.style.use('ggplot') # plot formatting

csv_filename = '2.csv'
data_headers = []
time_vec = []
accel_x,accel_y,accel_z,gyro_x,gyro_y,gyro_z = [],[],[],[],[],[]
with open(csv_filename,newline='') as csvfile:
    csvreader = csv.reader(csvfile,delimiter=",")
    for row in csvreader:
        if data_headers==[]:
            data_headers = row
            continue
        time_vec.append(float(row[0]))
        accel_x.append(float(row[1]))
        accel_y.append(float(row[2]))
        accel_z.append(float(row[3]))
        gyro_x.append(float(row[4]))
        gyro_y.append(float(row[5]))
        gyro_z.append(float(row[6]))
        

print('Sample Rate:  Hz'.format(samp_rate))

##########################

accel_x = np.array(accel_x)/accel_factor
accel_y = np.array(accel_y)/accel_factor
accel_z = np.array(accel_z)/accel_factor

gyro_x = np.array(gyro_x)/gyro_factor
gyro_y = np.array(gyro_y)/gyro_factor
gyro_z = np.array(gyro_z)/gyro_factor

##########################

cal_start = 0 # start calibration point
cal_end = 100 # end calibration point

# accel calibrations
a_x_cal = accel_x[cal_start:cal_end]
a_y_cal = accel_y[cal_start:cal_end]
a_z_cal = accel_z[cal_start:cal_end]

# gyro calibrations
g_x_cal = gyro_x[cal_start:cal_end]
g_y_cal = gyro_y[cal_start:cal_end]
g_z_cal = gyro_z[cal_start:cal_end]

# calculate accel & gyro calibration means
accel_offsets = [np.mean(a_x_cal),np.mean(a_y_cal),np.mean(a_z_cal)]
gyro_offsets = [np.mean(g_x_cal),np.mean(g_y_cal),np.mean(g_z_cal)]

grav_direc = np.argmax(accel_offsets) # location of gravity

# actual calculation of offset (subtracting starting means) 
accel_x = accel_x-accel_offsets[0]
accel_y = accel_y-accel_offsets[1]
accel_z = accel_z-accel_offsets[2]

gyro_x = gyro_x-gyro_offsets[0]
gyro_y = gyro_y-gyro_offsets[1]
gyro_z = gyro_z-gyro_offsets[2]

##########################


fig,ax = plt.subplots(2,1,figsize=(12,9))

ax1 = ax[0] # accel axis
cmap = plt.cm.Set1
print('Acceleration')
ax1.plot(time_vec,accel_x,label='x',color=cmap(1),linewidth=2)
ax1.plot(time_vec,accel_y,label='y',color=cmap(2),linewidth=2)
ax1.plot(time_vec,accel_z,label='z',color=cmap(0),linewidth=2)
ax1.legend(fontsize=16)


ax2 = ax[1] # gyro axis
cmap = plt.cm.tab10
ax2.plot(time_vec,gyro_x,label='x-gyroscope',color=cmap(1),linewidth=2)
ax2.plot(time_vec,gyro_y,label='y-gyroscope',color=cmap(4),linewidth=2)
ax2.plot(time_vec,gyro_z,label='z-gyroscope',color=cmap(6),linewidth=2)
ax2.legend(fontsize=16)
#ax2.set_ylabel('Degrees [$^\circ$]',fontsize=16)

plt.show()
