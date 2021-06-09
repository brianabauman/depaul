import { Component, OnInit, OnDestroy } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { Router, ActivatedRoute } from '@angular/router';
import { Subscription } from "rxjs";

import { BusinessCard } from '../business-card.model';
import { BusinessCardService } from '../business-card.service';
import { AuthService } from '../auth.service';

@Component({
  selector: 'app-add-business-card',
  templateUrl: './add-business-card.component.html',
  styleUrls: ['./add-business-card.component.css']
})
export class AddBusinessCardComponent implements OnInit, OnDestroy {
  addBusinessCardForm: FormGroup;
  text: string;
  paramSub: Subscription;

  constructor(
    private formBuilder: FormBuilder,
    private cardsService: BusinessCardService,
    private authService: AuthService,
    private router: Router,
    private route: ActivatedRoute
  ) { }

  ngOnInit() {
    this.paramSub = this.route.params.subscribe(params => {
      this.text = params["text"];
    });

    let card = this.extractBusinessCard(this.text);

    this.addBusinessCardForm = this.formBuilder.group({
        firstName: [card.firstName, Validators.required],
        lastName: [card.lastName, Validators.required],
        phoneNumber: [card.phoneNumber, Validators.required],
        emailAddress: [card.emailAddress, Validators.required],
        company: [card.company, Validators.required],
        additionalInfo: [card.additionalInfo]
    });
  }

  ngOnDestroy() {
    this.paramSub.unsubscribe();
  }

  // convenience getter for easy access to form fields
  get f() { return this.addBusinessCardForm.controls; }

  onSubmit() {
      // stop here if form is invalid
      if (this.addBusinessCardForm.invalid) {
        const controls = this.addBusinessCardForm.controls;
        let message = "Error:";
        for (const name in controls) {
          if (controls[name].invalid) {
            message += `\n A valid ${name} is required.`;
          }
        }

        alert(message);
        return;
      }

      console.log(this.f.firstName.value + ", " + 
        this.f.lastName.value + ", " + 
        this.f.phoneNumber.value + ", " + 
        this.f.emailAddress.value + ", " + 
        this.f.company.value + ", " + 
        this.f.additionalInfo.value);
      
      let card = new BusinessCard();
      card.firstName = this.f.firstName.value;
      card.lastName = this.f.lastName.value;
      card.phoneNumber = this.f.phoneNumber.value;
      card.emailAddress = this.f.emailAddress.value;
      card.company = this.f.company.value;
      card.additionalInfo = this.f.additionalInfo.value;

      this.cardsService.addCard(this.authService.userID, card);
      this.router.navigate(['home']);
  }

  extractBusinessCard(text: string): BusinessCard {
    const card = new BusinessCard();
    if (text) {
      let emailMatches = text.match(/\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+/);
      if (emailMatches && emailMatches.length > 0) {
        card.emailAddress = emailMatches[0];
      }

      let phoneMatches = text.match(/[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}/);
      if (phoneMatches && phoneMatches.length > 0) {
        card.phoneNumber = phoneMatches[0];
      }

      text = text.replace(card.phoneNumber, "");
      text = text.replace(card.emailAddress, "");

      const lines = text.split('\n');
      const name = lines[0];
      if (name.indexOf(' ') >= 0 ) {
        card.firstName = name.split(' ')[0];
        card.lastName = name.split(' ')[name.split(' ').length - 1];
      } else {
        card.firstName = name;
      }
      text = text.replace(name, "");

      if (lines.length > 1) { 
        card.company = lines[1]; 
        text = text.replace(card.company, "");
      }
      
      card.additionalInfo = text;
      console.log(card.additionalInfo);
    }

    return card;
  }
}
