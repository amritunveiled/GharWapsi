

---

Project Title

**GharWapsi – Real-Time Missing Person Tracker and Community Alert System**

---

Abstract

GharWapsi is an affordable, real-time, IoT-based system designed to help find missing persons through both GPS tracking hardware and community-powered mobile reporting. This system integrates a NodeMCU with GPS sensor that automatically sends live location to the cloud when an emergency button is pressed.
The data is shown on a mobile app developed using MIT App Inventor, allowing people to report a missing person, track them live (if wearing the device), or report a sighting. The app uses an open-source map API to show real-time locations, replacing costly and restrictive services like Google Maps. The system also includes visual indicators (LEDs) for button press feedback and upload status, ensuring a responsive interface.


<img width="648" height="293" alt="image" src="https://github.com/user-attachments/assets/f2ef1db2-7f01-4ed0-93fe-1bd960402b98" />

---
Objective

-Track missing persons in real-time using GPS and NodeMCU

-Enable users to report or spot someone through a user-friendly Android app

-Use open-source mapping solutions to reduce cost

-Build a scalable and simple prototype for public benefit

-Offer a unified app for both reporting and spotting users

---

System Architecture

1. Hardware Layer
NodeMCU ESP8266 – Controls GPS and uploads data
NEO-6M GPS – Provides coordinates
Button (4-pin) – Triggers location sharing
LEDs – Indicate data upload and button status

2. Software Layer
Firebase – Realtime Database, Auth, and Storage
MIT App Inventor – For building Android app without code
OpenStreetMap/Leaflet.js – For displaying real-time map locations

---

Hardware Features

-Real-time GPS tracking

-One-click emergency alert

-LEDs for status feedback

-Mobile App Features (MIT App Inventor)

-Sign in / Register functionality (Firebase)

-Submit missing person details with photo

-View live location from NodeMCU GPS

-Report sightings with details and image

-Open-source Map (OpenStreetMap) integration

-Real-time updates via Firebase

---

Backend Features

-Firebase Auth: User login and registration

-Firebase DB: Stores location and reports

-Firebase Storage: Upload and retrieve image

---

WorkFlow:

-Emergency Trigger

-Button press sends GPS data to Firebase

-App fetches and auto-displays location on open-source map

-User Reports Missing Person

-Info and photo submitted via app

-Visible to all users on map

-User Spots Someone

-Can report with photo and location

-Data appears live in app

---
Conclusion:

This version of GharWapsi offers an open, cost-effective, and easily replicable solution for missing person tracking. By utilizing MIT App Inventor and OpenStreetMap, the solution avoids platform restrictions while keeping the development and deployment entirely free. The addition of real-time GPS via NodeMCU and emergency triggers ensures faster intervention, giving families hope and communities a way to help.
