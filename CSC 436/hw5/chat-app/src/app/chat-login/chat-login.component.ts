import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { AuthService } from '../auth.service';

@Component({
  selector: 'chat-login',
  templateUrl: './chat-login.component.html',
  styleUrls: ['./chat-login.component.scss']
})
export class ChatLogin implements OnInit {
    loginForm: FormGroup;

    constructor(
        private formBuilder: FormBuilder,
        private router: Router,
        private authService: AuthService
    ) {
        //redirect to home if already logged in
        if (this.authService.user) { 
            this.router.navigate(['home']);
        }
    }

    ngOnInit() {
        this.loginForm = this.formBuilder.group({
            username: ['', Validators.required],
            password: ['', Validators.required]
        });
    }

    // convenience getter for easy access to form fields
    get f() { return this.loginForm.controls; }

    onSubmit() {
        // stop here if form is invalid
        if (this.loginForm.invalid) {
            return;
        }
        console.log(this.f.username.value + ", " + this.f.password.value);

        this.authService.login(this.f.username.value, this.f.password.value);
    }
}