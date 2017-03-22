package com.example.bonboru.sosolr;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class WelcomeActivity extends AppCompatActivity {

    public static WelcomeActivity welcomeActivity;
    public int id;
    public String lon, lat;
    public String name;
    private static LocationManager locationManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_welcome);
        welcomeActivity = this;

        locationManager = (LocationManager) getSystemService(LOCATION_SERVICE);
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            return;
        }
        locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 10000, 10, new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                lon = String.format("%.3f", location.getLongitude());
                lat = String.format("%.3f", location.getLatitude());
                ((TextView)findViewById(R.id.textView2)).setText("POSITION: " + lon + ", " + lat);
            }
            @Override
            public void onStatusChanged(String s, int i, Bundle bundle) {
            }
            @Override
            public void onProviderEnabled(String s) {
            }
            @Override
            public void onProviderDisabled(String s) {
            }
        });
    }

    public void register(View view) {
        Toast.makeText(this, "Successfully connected to SOS center, your profile has been registered.", Toast.LENGTH_SHORT).show();
        id = Integer.parseInt(((EditText)findViewById(R.id.editText3)).getText().toString());
        name = ((EditText)findViewById(R.id.editText4)).getText().toString();
        startActivity(new Intent(WelcomeActivity.this, HealthActivity.class));
    }
}
