{
    
    ifstream input;
    input.open("data.txt");
    
    TGraphErrors *ge = new TGraphErrors();
    ge->SetName("polGraph");
    
    TGraphErrors *ge2 = new TGraphErrors();
    ge2->SetName("polGraphReval");
    
    
    TF1 *fMig = new TF1("fMig","2.25e-3 * pow(x,5./3.)",1,250);
    
    
    TGraphErrors *geRatio = new TGraphErrors();
    geRatio->SetName("polRatioGraph");
    
    if(input.is_open())
    {
        int Z = 0, A = 0;
        double sigma_neg2 = 0, sigma_sigma = 0;
        
        while(input >> Z >>  A >> sigma_neg2 >> sigma_sigma)
        {
//             sigma_neg2*=1000; //convert to ub
//             printf("%d \t %d \t %f \t %f \n",Z,A,sigma_neg2,sigma_sigma);
            
            ge->SetPoint(ge->GetN(),A,sigma_neg2);
            
            if(sigma_sigma == 0)sigma_sigma = 0.1*sigma_neg2;
            
            ge->SetPointError(ge->GetN()-1,0,sigma_sigma);
            
            
            geRatio->SetPoint(geRatio->GetN(),A,sigma_neg2/fMig->Eval((double)A));
            geRatio->SetPointError(geRatio->GetN()-1,0,sigma_sigma/fMig->Eval((double)A));
        }
    }
    
    input.close();
    
    ge2->SetPoint(0,208,19.8);//208Pb
    ge2->SetPoint(1,90,3.69737);//90Zr
    ge2->SetPoint(2,112,5.22459);//112Sn
    //    ge2->SetPoint(2,92,);//92Zr
    ge2->SetMarkerStyle(8);
    ge2->SetMarkerColor(2);
    
    
    
    TCanvas *c1 = new TCanvas();
    
//     c1->SetLogx();
    c1->SetLogy();
    
    ge->Draw("AP");
    
    ge->GetXaxis()->CenterTitle();
    ge->GetXaxis()->SetTitle("Mass Number");
    
    ge->GetYaxis()->CenterTitle();
    ge->GetYaxis()->SetTitle("#sigma_{-2} [mb/MeV]");
    
    ge->SetMarkerStyle(8);
    
    ge2->Draw("P");
    
    ge->GetXaxis()->SetRangeUser(40,240);
    ge->SetMinimum(1);
    
    fMig->Draw("same");
    fMig->SetLineStyle(2);
    fMig->SetLineWidth(1);
    
    TCanvas *c2 = new TCanvas();
    
    geRatio->Draw("AP");
    geRatio->GetXaxis()->CenterTitle();
    geRatio->GetXaxis()->SetTitle("Mass Number");
    
    geRatio->GetYaxis()->CenterTitle();
    geRatio->GetYaxis()->SetTitle("Ratio #sigma_{-2}/Midgal Formula");
    
    geRatio->SetMarkerStyle(8);
    
//     c2->SetLogx();
    geRatio->GetXaxis()->SetRangeUser(40,240);
    
    geRatio->SetMaximum(2.0);
    geRatio->SetMinimum(0.05);
    
    TLine *line1 = new TLine(40,1,ge->GetPointX(ge->GetN()-1),1);
    line1->SetLineStyle(3);
    line1->Draw("same");
    
    TLine *line2 = new TLine(90,0.2,90,1.8);
    line2->SetLineStyle(4);
    line2->SetLineColor(4);
    line2->Draw("same");
    
    TLine *line3 = new TLine(138,0.2,138,1.8);
    line3->SetLineStyle(4);
    line3->SetLineColor(4);
    line3->Draw("same");
    
    TLine *line4 = new TLine(208,0.2,208,1.8);
    line4->SetLineStyle(4);
    line4->SetLineColor(4);
    line4->Draw("same");
    
    TGraphErrors *ge2Ratio = new TGraphErrors();
    ge2Ratio->SetTitle("ge2Ratio");
    
    for(int i=0;i<ge2->GetN();i++)
    {
        ge2Ratio->SetPoint(ge2Ratio->GetN(),ge2->GetPointX(i),ge2->GetPointY(i)/fMig->Eval(ge2->GetPointX(i)));
    }
    
    ge2Ratio->Draw("P");
    ge2Ratio->SetMarkerColor(2);
    ge2Ratio->SetMarkerStyle(8);
}
