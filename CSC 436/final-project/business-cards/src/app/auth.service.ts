import { Injectable } from '@angular/core';
import { AngularFireAuth } from '@angular/fire/auth';
import { Router } from '@angular/router';
import * as firebase from 'firebase/app';

import { Observable } from 'rxjs';
import { BusinessCardService } from './business-card.service';
import { ReturnStatement } from '@angular/compiler';

@Injectable()
export class AuthService {
  user: Observable<firebase.User>;
  userID: string;
  loggedIn: boolean;

  constructor(
      private firebaseAuth: AngularFireAuth, 
      private router: Router,
      private cardsService: BusinessCardService
    ) {
    this.user = firebaseAuth.authState;
    this.loggedIn = false;
    this.firebaseAuth.authState.subscribe(user => { 
      this.userID = user.uid;
    });
  }

  login(email: string, password: string) {
    this.firebaseAuth
      .auth
      .signInWithEmailAndPassword(email, password)
      .then((userCred) => {
        console.log("login successful, uid: " + userCred.user.uid);
        this.loggedIn = true;
        this.userID = userCred.user.uid;
        this.router.navigate(['home']);
      })
      .catch(err => {
        this.loggedIn = false;
        this.userID = "";
        alert("Login error: " + err.message);
      });
  }

  logout() {
    this.firebaseAuth
      .auth
      .signOut();
    this.loggedIn = false;
    this.router.navigate(['login']);
  }
  
  isLoggedIn(): boolean {
    return this.loggedIn;
  }

  register(email: string, password: string) {
    this.firebaseAuth
      .auth
      .createUserWithEmailAndPassword(email, password)
      .then((userCred) => {
        console.log("registration successful, uid: " + userCred.user.uid);
        this.loggedIn = true;
        this.userID = userCred.user.uid;
        this.cardsService.createCollection(this.userID);
        this.router.navigate(['home']);
      })
      .catch(err => {
        this.loggedIn = false;
        this.userID = "";
        alert("Registration error: " + err.message);
      });
  }
}