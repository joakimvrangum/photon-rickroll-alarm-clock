package com.vrangum.android.vekkerklokkeapp;

import android.app.Activity;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.DialogFragment;
import android.support.v7.app.AlertDialog;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TimePicker;

import java.util.Calendar;
import java.util.Date;

/**
 * Created by Joakim on 11/04/2018.
 */

public class TimepickerFragment extends DialogFragment {
    private static final String ARG_TIME = "time";
    public static final String EXTRA_TIME = "com.vrangum.android.vekkerklokkeapp.time";
    private TimePicker mTimePicker;

    public static TimepickerFragment newInstance(Date time) {
        Bundle args = new Bundle();
        args.putSerializable(ARG_TIME, time);

        TimepickerFragment fragment = new TimepickerFragment();
        fragment.setArguments(args);
        return fragment;
    }


    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        final Date time = (Date) getArguments().getSerializable(ARG_TIME);

        final Calendar calendar = Calendar.getInstance();
        calendar.setTime(time);
        int hour = calendar.get(Calendar.HOUR);
        int mins = calendar.get(Calendar.MINUTE);

        View v = LayoutInflater.from(getActivity()).inflate(R.layout.dialog_time, null);

        mTimePicker = (TimePicker) v.findViewById(R.id.dialog_time_picker);
        mTimePicker.setCurrentHour(hour);
        mTimePicker.setCurrentMinute(mins);

        return new AlertDialog.Builder(getActivity())
                .setView(v)
                .setTitle(R.string.title_timepicker)
                .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        int hour = mTimePicker.getCurrentHour();
                        int mins = mTimePicker.getCurrentMinute();

                        Calendar calendarTime = Calendar.getInstance();
                        calendarTime.setTime(time);
                        calendarTime.set(Calendar.HOUR, hour);
                        calendarTime.set(Calendar.MINUTE, mins);
                        Date time = calendarTime.getTime();
                        sendResult(Activity.RESULT_OK, time);
                    }
                })
                .create();
    }



    private void sendResult(int resultCode, Date time) {
        if (getTargetFragment() == null) {
            return;
        }

        Intent intent = new Intent();
        intent.putExtra(EXTRA_TIME, time);

        getTargetFragment().onActivityResult(getTargetRequestCode(),
                resultCode,
                intent);
    }
}
