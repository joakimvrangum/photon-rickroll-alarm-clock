package com.vrangum.android.vekkerklokkeapp;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.URL;
import java.util.Date;

import javax.net.ssl.HttpsURLConnection;

/**
 * Created by Joakim on 11/04/2018.
 */

public class VekkerklokkeFragment extends Fragment {
    private static final String TAG = "VekkerklokkeAppen";
    private static final String DIALOG_TIME = "DialogTime";
    public static final String TIMEFORMAT_SERVER = "hhmm";
    public static final String TIMEFORMAT_APP = "hh:mm";
    private static final int REQUEST_TIME = 1;
    private AlarmTime mAlarmTime;
    Button mTimeButton;
    Button mSetAlarmButton;
    Button mDeleteAlarmButton;
    TextView mTimeLabel;
    ImageView mRickImage;


    public static VekkerklokkeFragment newInstance() {
        return new VekkerklokkeFragment();
    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRetainInstance(true);
        mAlarmTime = new AlarmTime();
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_vekkerklokke, container, false);

        /* Textview for alarmtidspunkt */
        mTimeLabel = (TextView) v.findViewById(R.id.textview_alarmtime);

        /* Tidspunkt-knappen */
        mTimeButton = (Button) v.findViewById(R.id.btn_pick_time);
        //updateTimeUI();
        mTimeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FragmentManager manager = getFragmentManager();
                TimepickerFragment dialog = TimepickerFragment.newInstance(mAlarmTime.getTime());
                dialog.setTargetFragment(VekkerklokkeFragment.this, REQUEST_TIME);
                dialog.show(manager, DIALOG_TIME);
            }
        });

        /* Sett Alarm-knappen */
        mSetAlarmButton = (Button) v.findViewById(R.id.btn_set_alarm);
        mSetAlarmButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                android.text.format.DateFormat df = new android.text.format.DateFormat();
                new PostClient().execute(df.format(TIMEFORMAT_SERVER, mAlarmTime.getTime()).toString());
                Toast.makeText(getContext(),"Alarm er aktivert på vekkerklokken!",Toast.LENGTH_SHORT).show();
                mDeleteAlarmButton.setEnabled(true);
                mRickImage.setVisibility(View.VISIBLE);
            }
        });

        /* Slett Alarm-knappen */
        mDeleteAlarmButton = (Button) v.findViewById(R.id.btn_delete_alarm);
        mDeleteAlarmButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                new PostClientDeleteAlarm().execute("SLETT_ALARM");
                mSetAlarmButton.setEnabled(true);
                mRickImage.setVisibility(View.INVISIBLE);
            }
        });

        mRickImage = (ImageView) v.findViewById(R.id.image_rick);
        return v;
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == REQUEST_TIME) {
            Date time = (Date) data.getSerializableExtra(TimepickerFragment.EXTRA_TIME);
            mAlarmTime.setTime(time);
            updateTimeUI();
        }
    }

    /**
     * Oppdaterer Textview til tidspunktet valgt
     */
    private void updateTimeUI() {
        android.text.format.DateFormat df = new android.text.format.DateFormat();
        mTimeLabel.setText("Alarm satt: " + df.format(TIMEFORMAT_APP, mAlarmTime.getTime()).toString());
        mSetAlarmButton.setEnabled(true);
    }


    /**
     * Poster Alarmtidspunktet til Particle
     */
    class PostClient extends AsyncTask<String, Void, String> {
        public String doInBackground(String... IO) {

            String io = new String(IO[0]);
            URL url;

            try {
                url = new URL("https://api.particle.io/v1/devices/YOUR_DEVICE_ID_GOES_HERE/setalarm");
                String param = "access_token=_YOUR_ACCESS_TOKEN_GOES_HERE&args="+io;
                Log.d(TAG, "param:" + param);

                HttpsURLConnection con = (HttpsURLConnection) url.openConnection();
                con.setReadTimeout(7000);
                con.setConnectTimeout(7000);
                con.setDoOutput(true);
                con.setDoInput(true);
                con.setInstanceFollowRedirects(false);
                con.setRequestMethod("POST");
                con.setFixedLengthStreamingMode(param.getBytes().length);
                con.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");

                PrintWriter out = new PrintWriter(con.getOutputStream());
                out.print(param);
                out.close();

                con.connect();

                BufferedReader in = null;
                if (con.getResponseCode() != 200) {
                    in = new BufferedReader(new InputStreamReader(con.getErrorStream()));
                } else {
                    in = new BufferedReader(new InputStreamReader(con.getInputStream()));
                };
                mSetAlarmButton.setEnabled(false);

            } catch (Exception e) {
                Log.d(TAG, "Feilet ");
                e.printStackTrace();
                return null;
            }
            return null;
        }
    }

    /**
     * Sletter alarm - kunnne vært slått sammen med PostClient til en metode, men gidder ikke refactore nå...
     */
    class PostClientDeleteAlarm extends AsyncTask<String, Void, String> {
        public String doInBackground(String... IO) {

            String io = new String(IO[0]);
            URL url;

            try {
                url = new URL("https://api.particle.io/v1/devices/YOUR_DEVICE_ID_GOES_HERE/deletealarm");
                String param = "access_token=_YOUR_ACCESS_TOKEN_GOES_HERE&args="+io;
                Log.d(TAG, "param:" + param);

                HttpsURLConnection con = (HttpsURLConnection) url.openConnection();
                con.setReadTimeout(7000);
                con.setConnectTimeout(7000);
                con.setDoOutput(true);
                con.setDoInput(true);
                con.setInstanceFollowRedirects(false);
                con.setRequestMethod("POST");
                con.setFixedLengthStreamingMode(param.getBytes().length);
                con.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");

                PrintWriter out = new PrintWriter(con.getOutputStream());
                out.print(param);
                out.close();

                con.connect();

                BufferedReader in = null;
                if (con.getResponseCode() != 200) {
                    in = new BufferedReader(new InputStreamReader(con.getErrorStream()));
                } else {
                    in = new BufferedReader(new InputStreamReader(con.getInputStream()));
                };


            } catch (Exception e) {
                Log.d(TAG, "Feilet ");
                e.printStackTrace();
                return null;
            }
            return null;
        }
    }
}
