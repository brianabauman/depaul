import { Injectable } from '@angular/core';
import { AngularFireAuth } from '@angular/fire/auth';
import { Router } from '@angular/router';
import * as firebase from 'firebase/app';
import { first } from 'rxjs/operators';

import { Observable } from 'rxjs';

@Injectable()
export class AuthService {
  user: Observable<firebase.User>;
  loggedIn: boolean;

  constructor(private firebaseAuth: AngularFireAuth,
             private router: Router) {
    this.user = firebaseAuth.authState;
  }

  login(email: string, password: string) {
    this.firebaseAuth
      .auth
      .signInWithEmailAndPassword(email, password)
      .then((userCred) => {
        console.log('Nice, it worked! uid: ' + userCred.user.uid);
        this.loggedIn = true;
        this.router.navigate(['/home']);
      })
      .catch(err => {
        console.log('Something went wrong:',err.message);
        this.loggedIn = false;
        alert("Invalid username/password.");
      });
  }

  logout() {
    this.firebaseAuth
      .auth
      .signOut();
    this.loggedIn = false;
    console.log("signed out")
  }

  isLoggedIn(): boolean {
    return this.loggedIn;
  }
}