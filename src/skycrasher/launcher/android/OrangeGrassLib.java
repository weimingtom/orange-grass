/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package skycrasher.launcher.android;

// Wrapper for native library

public class OrangeGrassLib {

     static {
         System.loadLibrary("orangegrass");
     }

    /**
     * @param width the current view width
     * @param height the current view height
     * @param assetPath the path to assets
     */
     public static native void init(int width, int height, String assetPath);
     public static native void step();
     /**
      * @param x the current touch x coordinate
      * @param y the current touch y coordinate
      */
     public static native void ontouch(float x, float y);
}
