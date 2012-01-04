package skycrasher.launcher.android;

import android.app.Activity;
import android.os.Bundle;


public class OrangeGrassActivity extends Activity {

    OrangeGrassView mView;

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        mView = new OrangeGrassView(getApplication());
	setContentView(mView);
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
}
