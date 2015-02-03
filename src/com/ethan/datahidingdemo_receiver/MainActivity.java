package com.ethan.datahidingdemo_receiver;

import java.io.File;
import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.dropbox.client2.DropboxAPI;
import com.dropbox.client2.android.AndroidAuthSession;
import com.dropbox.client2.android.AuthActivity;
import com.dropbox.client2.session.AccessTokenPair;
import com.dropbox.client2.session.AppKeyPair;

import org.apache.commons.io.FileUtils;

import ru.bartwell.exfilepicker.ExFilePicker;
import ru.bartwell.exfilepicker.ExFilePickerParcelObject;
import info.guardianproject.f5android.*;

public class MainActivity extends Activity {
	
	
	private static final String TAG = "DataHidingDemo-Reciever";

    final static private String APP_KEY = "hca6eo97efahfi5";
    final static private String APP_SECRET = "t9ue5abgn4gprb0";

    final static private String ACCOUNT_PREFS_NAME = "prefs";
    final static private String ACCESS_KEY_NAME = "ACCESS_KEY";
    final static private String ACCESS_SECRET_NAME = "ACCESS_SECRET";
    private final static String IMAGE_FILE_NAME = "recieved.jpg";
    private final static String MSG_FILE_NAME = "ReceivedMsg.txt";
   
    private String mSelectedFileName;
    

    private static final boolean USE_OAUTH1 = false;
    private static final int EX_FILE_PICKER_RESULT = 0;

    DropboxAPI<AndroidAuthSession> mApi;

    private boolean mLoggedIn;

    // Android widgets
    private Button mSubmit;
    private LinearLayout mDisplay;
    private Button mDecrypt;
    private Button mDownload;
    private TextView moriginMessage;
    private ImageView mImage;
    private ImageButton mFindFile;
    private Button mDecryptFile;

    private final String PHOTO_DIR = "/Photos/";

    final static private int NEW_PICTURE = 1;
    private String mCameraFileName=null;
    public Activity activity = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        activity=this;

        AndroidAuthSession session = buildSession();
        mApi = new DropboxAPI<AndroidAuthSession>(session);

        setContentView(R.layout.activity_main);
        checkAppKeySetup();

        mSubmit = (Button)findViewById(R.id.auth_button);
        moriginMessage = (TextView) findViewById(R.id.originMessage);

        mSubmit.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                // This logs you out if you're logged in, or vice versa
                if (mLoggedIn) {
                    logOut();
                } else {
                    // Start the remote authentication
                    if (USE_OAUTH1) {
                        mApi.getSession().startAuthentication(MainActivity.this);
                    } else {
                        mApi.getSession().startOAuth2Authentication(MainActivity.this);
                    }
                }
            }
        });

        mDisplay = (LinearLayout)findViewById(R.id.logged_in_display);

        // This is where a photo is displayed
        mImage = (ImageView)findViewById(R.id.image_view);

        mDownload = (Button)findViewById(R.id.download_button);

        mDownload.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                DownloadPicture download = new DownloadPicture(MainActivity.this, mApi, PHOTO_DIR, mImage);
                download.execute();
                moriginMessage.setText("Decrypted Message to be shown here");
                //moriginMessage.clearComposingText();
            }
        });

        mFindFile = (ImageButton)findViewById(R.id.browse_File);
        mFindFile.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	Intent intent = new Intent(getApplicationContext(), ru.bartwell.exfilepicker.ExFilePickerActivity.class);
            	intent.putExtra(ExFilePicker.SET_ONLY_ONE_ITEM, true);
            	intent.putExtra(ExFilePicker.SET_FILTER_LISTED, new String[] { "jpg", "jpeg","pdf" });
            	intent.putExtra(ExFilePicker.DISABLE_NEW_FOLDER_BUTTON, true);
            	intent.putExtra(ExFilePicker.SET_CHOICE_TYPE, ExFilePicker.CHOICE_TYPE_FILES);
            	startActivityForResult(intent, EX_FILE_PICKER_RESULT);
            }
        });
        
        mDecrypt =(Button)findViewById(R.id.Decrypt_button);
        mDecrypt.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            
            	File sdCard = Environment.getExternalStorageDirectory();

                File receivedFile = new File ("/sdcard/receiver/"+IMAGE_FILE_NAME);
               
                if(receivedFile.exists()){
                	
                	Extract aExtract= new Extract(activity, receivedFile);
                
                //	int result = nativeDecrypt("/sdcard/receiver/received.dat","Init");
                	//moriginMessage.setText(DecryptedMsg);
                	
                	File file = new File("/sdcard/receiver/received.dat");//("/sdcard/receiver/decrypted.dat");
                	
                	try
                	{
                		byte [] fileBytes = FileUtils.readFileToByteArray(file);
                		String str = new String(fileBytes, "UTF-8");

                		int flag = fileBytes[0];
                		int i;
                    	if (flag==50){
                    		String subString = str.substring(1,str.length()) ;
                    		moriginMessage.setText(subString);
                    	}
                	}
                	catch (IOException e) {
                		e.printStackTrace();
                	}
                	
                		
                	
                	showToast("SteganographyDecode Msg Succeeded!");
                	
                	//try {
                	  // String str = FileUtils.readFileToString(new File( sdCard.getAbsolutePath() + "/receiver/"+"ReceivedMsgdecrypted.txt"));
                	  // moriginMessage.setText(str);
                	// } catch (IOException e) {
                	 //   e.printStackTrace();
                	//}
                	
                	//showToast("SteganographyDecode Msg Succeeded!");
            	}
                
                
            }
        });

        mDecryptFile = (Button)findViewById(R.id.decrypt_File);
        mDecryptFile.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            
            	File sdCard = Environment.getExternalStorageDirectory();

                File receivedFile = new File ("/sdcard/receiver/"+IMAGE_FILE_NAME);
               
                if(receivedFile.exists()){
                	int result= SteganographyFileDecode(receivedFile.toString());
                	result = nativeBinaryDecrypt("/sdcard/receiver/ReceiveEncryptedFile.dat","Init");
                	
                    if(result==0){
                	     	showToast("SteganographyDecode File Succeeded!");
                	     
                    }
            	}
                
                
            }
        });
        setLoggedIn(mApi.getSession().isLinked());

    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        outState.putString("mCameraFileName", mCameraFileName);
        super.onSaveInstanceState(outState);
    }

    @Override
    protected void onResume() {
        super.onResume();
        AndroidAuthSession session = mApi.getSession();

        // The next part must be inserted in the onResume() method of the
        // activity from which session.startAuthentication() was called, so
        // that Dropbox authentication completes properly.
        if (session.authenticationSuccessful()) {
            try {
                // Mandatory call to complete the auth
                session.finishAuthentication();

                // Store it locally in our app for later use
                storeAuth(session);
                setLoggedIn(true);
            } catch (IllegalStateException e) {
                showToast("Couldn't authenticate with Dropbox:" + e.getLocalizedMessage());
                Log.i(TAG, "Error authenticating", e);
            }
        }
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
    	if (requestCode == EX_FILE_PICKER_RESULT) {
			if (data != null) {
				ExFilePickerParcelObject object = (ExFilePickerParcelObject) data.getParcelableExtra(ExFilePickerParcelObject.class.getCanonicalName());
				if (object.count > 0) {
					StringBuffer buffer = new StringBuffer();
					for (int i = 0; i < object.count; i++) {
						buffer.append(object.names.get(i));
						if (i < object.count - 1) buffer.append(", ");
					}
					mSelectedFileName=object.path + buffer.toString();
					showToast(mSelectedFileName);
					Bitmap myBitmap = BitmapFactory.decodeFile(mSelectedFileName);
        	     	mImage.setImageBitmap(myBitmap);
					//((TextView) findViewById(R.id.result)).setText("Count: " + object.count + "\n" + "Path: " + object.path + "\n" + "Selected: " + buffer.toString());
				}
			}
		}
		        
    }


    private void logOut() {
        // Remove credentials from the session
        mApi.getSession().unlink();

        // Clear our stored keys
        clearKeys();
        // Change UI state to display logged out version
        setLoggedIn(false);
    }

    /**
     * Convenience function to change UI state based on being logged in
     */
    private void setLoggedIn(boolean loggedIn) {
        mLoggedIn = loggedIn;
        if (loggedIn) {
            mSubmit.setText("Unlink from Dropbox");
            mDisplay.setVisibility(View.VISIBLE);
        } else {
            mSubmit.setText("Link with Dropbox");
            mDisplay.setVisibility(View.GONE);
            mImage.setImageDrawable(null);
        }
    }

    private void checkAppKeySetup() {
        // Check to make sure that we have a valid app key
        if (APP_KEY.startsWith("CHANGE") ||
                APP_SECRET.startsWith("CHANGE")) {
            showToast("You must apply for an app key and secret from developers.dropbox.com, and add them to the DBRoulette ap before trying it.");
            finish();
            return;
        }

        // Check if the app has set up its manifest properly.
        Intent testIntent = new Intent(Intent.ACTION_VIEW);
        String scheme = "db-" + APP_KEY;
        String uri = scheme + "://" + AuthActivity.AUTH_VERSION + "/test";
        testIntent.setData(Uri.parse(uri));
        PackageManager pm = getPackageManager();
        if (0 == pm.queryIntentActivities(testIntent, 0).size()) {
            showToast("URL scheme in your app's " +
                    "manifest is not set up correctly. You should have a " +
                    "com.dropbox.client2.android.AuthActivity with the " +
                    "scheme: " + scheme);
            finish();
        }
    }

    private void showToast(String msg) {
        Toast error = Toast.makeText(this, msg, Toast.LENGTH_LONG);
        error.show();
    }

    /**
     * Shows keeping the access keys returned from Trusted Authenticator in a local
     * store, rather than storing user name & password, and re-authenticating each
     * time (which is not to be done, ever).
     */
    private void loadAuth(AndroidAuthSession session) {
        SharedPreferences prefs = getSharedPreferences(ACCOUNT_PREFS_NAME, 0);
        String key = prefs.getString(ACCESS_KEY_NAME, null);
        String secret = prefs.getString(ACCESS_SECRET_NAME, null);
        if (key == null || secret == null || key.length() == 0 || secret.length() == 0) return;

        if (key.equals("oauth2:")) {
            // If the key is set to "oauth2:", then we can assume the token is for OAuth 2.
            session.setOAuth2AccessToken(secret);
        } else {
            // Still support using old OAuth 1 tokens.
            session.setAccessTokenPair(new AccessTokenPair(key, secret));
        }
    }

    /**
     * Shows keeping the access keys returned from Trusted Authenticator in a local
     * store, rather than storing user name & password, and re-authenticating each
     * time (which is not to be done, ever).
     */
    private void storeAuth(AndroidAuthSession session) {
        // Store the OAuth 2 access token, if there is one.
        String oauth2AccessToken = session.getOAuth2AccessToken();
        if (oauth2AccessToken != null) {
            SharedPreferences prefs = getSharedPreferences(ACCOUNT_PREFS_NAME, 0);
            Editor edit = prefs.edit();
            edit.putString(ACCESS_KEY_NAME, "oauth2:");
            edit.putString(ACCESS_SECRET_NAME, oauth2AccessToken);
            edit.commit();
            return;
        }
        // Store the OAuth 1 access token, if there is one.  This is only necessary if
        // you're still using OAuth 1.
        AccessTokenPair oauth1AccessToken = session.getAccessTokenPair();
        if (oauth1AccessToken != null) {
            SharedPreferences prefs = getSharedPreferences(ACCOUNT_PREFS_NAME, 0);
            Editor edit = prefs.edit();
            edit.putString(ACCESS_KEY_NAME, oauth1AccessToken.key);
            edit.putString(ACCESS_SECRET_NAME, oauth1AccessToken.secret);
            edit.commit();
            return;
        }
    }

    private void clearKeys() {
        SharedPreferences prefs = getSharedPreferences(ACCOUNT_PREFS_NAME, 0);
        Editor edit = prefs.edit();
        edit.clear();
        edit.commit();
    }

    private AndroidAuthSession buildSession() {
        AppKeyPair appKeyPair = new AppKeyPair(APP_KEY, APP_SECRET);

        AndroidAuthSession session = new AndroidAuthSession(appKeyPair);
        loadAuth(session);
        return session;
    }


    
    public native int SteganographyDecode(String imagePathName);
    public native int SteganographyFileDecode(String imagePathName);
    public native byte[] nativeEncrypt(String aplaintext, String amasterkey);
    public native int nativeDecrypt(String aciphertextFilePath,String amasterkey);
    public native int nativeBinaryDecrypt(String binaryFilePath, String amasterkey);
   
    static {
        	System.loadLibrary("datahidingdemoreceiver");
        	System.loadLibrary("opencv_java");
    	  
    }


}
