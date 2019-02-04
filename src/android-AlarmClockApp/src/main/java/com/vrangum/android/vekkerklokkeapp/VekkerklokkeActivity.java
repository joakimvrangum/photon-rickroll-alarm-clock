package com.vrangum.android.vekkerklokkeapp;

import android.support.v4.app.Fragment;

public class VekkerklokkeActivity extends SingleFragmentActivity {

    @Override
    protected Fragment createFragment() {
        return VekkerklokkeFragment.newInstance();
    }
}
