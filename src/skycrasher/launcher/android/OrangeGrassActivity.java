package skycrasher.launcher.android;

import android.app.Activity;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;


public class OrangeGrassActivity extends Activity 
{
    OrangeGrassView mView;
    SensorManager mSensorManager;
    Sensor mAccelerometer;

    @Override protected void onCreate(Bundle icicle) 
    {
        super.onCreate(icicle);
        mSensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
        mView = new OrangeGrassView(getApplication());
        mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
	    setContentView(mView);
    }

    @Override protected void onPause() 
    {
        super.onPause();
        mView.onPause();
        mSensorManager.unregisterListener(mView);
    }

    @Override protected void onStop() 
    {
    	super.onStop();
    	finish();
    }

    @Override protected void onResume() 
    {
        super.onResume();
        mView.onResume();
        mSensorManager.registerListener(mView, mAccelerometer, SensorManager.SENSOR_DELAY_GAME);
    }

    @Override protected void onDestroy() 
    {
    	super.onDestroy();
        mSensorManager.unregisterListener(mView);
    	mView.onDestroy();
    }
}
