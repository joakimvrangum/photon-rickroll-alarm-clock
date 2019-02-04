package com.vrangum.android.vekkerklokkeapp;

import java.util.Date;

/**
 * Created by Joakim on 11/04/2018.
 */

public class AlarmTime {
    private Date mTime;

    public AlarmTime() {
        mTime = new Date();
    }

    public AlarmTime(Date time) {
        mTime = time;
    }

    public Date getTime() {
        return mTime;
    }

    public void setTime(Date time) {
        mTime = time;
    }
}
